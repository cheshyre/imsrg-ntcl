// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/two_body/operator.h"

#include <memory>
#include <utility>
#include <vector>

#include "ntcl/data/f_array.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/model_space.h"
#include "imsrg/model_space/scalar/two_body/pandya_channel_key.h"
#include "imsrg/quantum_numbers/coupling/factors.h"
#include "imsrg/quantum_numbers/coupling/wigner_symbols.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

namespace detail {
void AddPandyaContribution(const ntcl::FArray<double, 4>& input,
                           std::size_t dim_p, std::size_t dim_q,
                           std::size_t dim_r, std::size_t dim_s, double factor,
                           ntcl::FArray<double, 4>& destination);
}

Scalar2BOperator Scalar2BOperator::FromScalar2BModelSpace(
    const std::shared_ptr<const Scalar2BModelSpace>& ms_ptr, Hermiticity herm) {
  std::vector<ntcl::FArray<double, 4>> tensors;
  tensors.reserve(ms_ptr->NumberOfChannels());

  for (std::size_t index = 0; index < ms_ptr->size(); index++) {
    const auto& chan = ms_ptr->ChannelAtIndex(index);
    const auto dim_i = chan.BraChannel1().size();
    const auto dim_j = chan.BraChannel2().size();
    const auto dim_k = chan.KetChannel1().size();
    const auto dim_l = chan.KetChannel2().size();

    tensors.emplace_back(dim_i, dim_j, dim_k, dim_l);
  }

  Ensures(ms_ptr->NumberOfChannels() == tensors.size());

  return Scalar2BOperator(ms_ptr, herm, std::move(tensors));
}

Scalar2BOperator::Scalar2BOperator(
    const std::shared_ptr<const Scalar2BModelSpace>& ms_ptr, Hermiticity herm,
    std::vector<ntcl::FArray<double, 4>>&& tensors)
    : ms_ptr_(ms_ptr), herm_(herm), tensors_(std::move(tensors)) {
  Expects(ms_ptr_->NumberOfChannels() == tensors_.size());
}

ntcl::FArray<double, 4> Scalar2BOperator::GeneratePandyaTensorInPandyaChannel(
    const Scalar2BPandyaChannelKey& pandya_channel) const {
  // TODO(mheinz): test
  const auto [chan_p, chan_s, chan_r, chan_q] =
      pandya_channel.SingleParticleChannels();
  const auto dim_p = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_p);
  const auto dim_q = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_q);
  const auto dim_r = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_r);
  const auto dim_s = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_s);

  const auto jj_p = chan_p.JJ().AsJJ();
  const auto jj_q = chan_q.JJ().AsJJ();
  const auto jj_r = chan_r.JJ().AsJJ();
  const auto jj_s = chan_s.JJ().AsJJ();
  const auto jj_2b_pand = pandya_channel.OperatorChannel().JJ().AsJJ();

  const auto& wigner_engine = WignerSymbolEngine::GetInstance();

  ntcl::FArray<double, 4> tensor(dim_p, dim_s, dim_r, dim_q);

  const auto standard_chankeys = pandya_channel.StandardChannels();
  for (const auto& chankey : standard_chankeys) {
    const auto index = ms_ptr_->IndexOfChannelInModelSpace(chankey);
    const auto& standard_tensor = GetTensorAtIndex(index);

    const auto jj_2b_standard = chankey.OpChannel().JJ().AsJJ();

    double chan_factor = -1 * imsrg::HatSquared(jj_2b_standard) *
                         wigner_engine.Wigner6J(jj_p, jj_s, jj_2b_pand, jj_r,
                                                jj_q, jj_2b_standard);

    imsrg::detail::AddPandyaContribution(standard_tensor, dim_p, dim_q, dim_r,
                                         dim_s, chan_factor, tensor);
  }

  return tensor;
}

void Scalar2BOperator::AddPandyaTensor(
    const Scalar2BPandyaChannelKey& pandya_channel,
    const ntcl::FArray<double, 4>& pandya_tensor, double factor) {
  // TODO(mheinz): test
  const auto [chan_p, chan_s, chan_r, chan_q] =
      pandya_channel.SingleParticleChannels();
  const auto dim_p = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_p);
  const auto dim_q = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_q);
  const auto dim_r = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_r);
  const auto dim_s = ms_ptr_->SingleParticleModelSpace().ChannelDim(chan_s);

  const auto jj_p = chan_p.JJ().AsJJ();
  const auto jj_q = chan_q.JJ().AsJJ();
  const auto jj_r = chan_r.JJ().AsJJ();
  const auto jj_s = chan_s.JJ().AsJJ();
  const auto jj_2b_pand = pandya_channel.OperatorChannel().JJ().AsJJ();

  const auto& wigner_engine = WignerSymbolEngine::GetInstance();

  const auto standard_chankeys = pandya_channel.StandardChannels();
  for (const auto& chankey : standard_chankeys) {
    const auto index = ms_ptr_->IndexOfChannelInModelSpace(chankey);
    auto& standard_tensor = GetMutableTensorAtIndex(index);

    const auto jj_2b_standard = chankey.OpChannel().JJ().AsJJ();

    double chan_factor = -1 * imsrg::HatSquared(jj_2b_pand) *
                         wigner_engine.Wigner6J(jj_p, jj_q, jj_2b_standard,
                                                jj_r, jj_s, jj_2b_pand);

    imsrg::detail::AddPandyaContribution(pandya_tensor, dim_p, dim_s, dim_r,
                                         dim_q, factor * chan_factor,
                                         standard_tensor);
  }
}

namespace detail {

void AddPandyaContribution(const ntcl::FArray<double, 4>& input,
                           std::size_t dim_p, std::size_t dim_q,
                           std::size_t dim_r, std::size_t dim_s, double factor,
                           ntcl::FArray<double, 4>& destination) {
  for (std::size_t s = 0; s < dim_s; s += 1) {
    for (std::size_t r = 0; r < dim_r; r += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          destination(p, s, r, q) += factor * input(p, q, r, s);
        }
      }
    }
  }
}
}  // namespace detail
}  // namespace imsrg
