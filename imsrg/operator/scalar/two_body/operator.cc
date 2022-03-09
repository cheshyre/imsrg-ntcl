// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/two_body/operator.h"

#include <memory>
#include <utility>
#include <vector>

#include "ntcl/data/f_array.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/model_space.h"
#include "imsrg/model_space/scalar/two_body/pandya_channel_key.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

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
  // TODO(mheinz): implement
  return ntcl::FArray<double, 4>(1, 1, 1, 1);
}

void Scalar2BOperator::AddPandyaTensor(
    const Scalar2BPandyaChannelKey& pandya_channel,
    const ntcl::FArray<double, 4>& pandya_tensor, double factor) {
  // TODO(mheinz): implement
}

}  // namespace imsrg
