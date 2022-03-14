// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/two_body/antisymmetry.h"

#include "ntcl/data/f_array.h"
#include "spdlog/spdlog.h"

#include "imsrg/model_space/scalar/two_body/antisymmetry.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {

void AntisymmetrizeOperatorInChannel(Scalar2BOperator& op,
                                     Scalar2BChannelKey chankey) {
  if (!IsChannelInMinimalAntisymmetricSet(chankey)) {
    return;
  }

  const auto& ms_2b = op.GetModelSpace();
  const auto& sp_ms = ms_2b.SingleParticleModelSpace();

  const auto dim_p = sp_ms.ChannelDim(chankey.BraChannelKey().p_chan_key);
  const auto dim_q = sp_ms.ChannelDim(chankey.BraChannelKey().q_chan_key);
  const auto dim_r = sp_ms.ChannelDim(chankey.KetChannelKey().p_chan_key);
  const auto dim_s = sp_ms.ChannelDim(chankey.KetChannelKey().q_chan_key);

  // spdlog::info("dims = {} {} {} {}", dim_p, dim_q, dim_r, dim_s);

  ntcl::FArray<double, 4> temp_pqrs(dim_p, dim_q, dim_r, dim_s);

  const auto [chankey_qprs, chankey_pqsr, chankey_qpsr] =
      GeneratePermutedChannels(chankey);
  const auto [factor_qprs, factor_pqsr, factor_qpsr] =
      GeneratePermutationFactors(chankey);

  const auto index_pqrs = ms_2b.IndexOfChannelInModelSpace(chankey);
  const auto index_qprs = ms_2b.IndexOfChannelInModelSpace(chankey_qprs);
  const auto index_pqsr = ms_2b.IndexOfChannelInModelSpace(chankey_pqsr);
  const auto index_qpsr = ms_2b.IndexOfChannelInModelSpace(chankey_qpsr);

  auto& tensor_pqrs = op.GetMutableTensorAtIndex(index_pqrs);
  auto& tensor_qprs = op.GetMutableTensorAtIndex(index_qprs);
  auto& tensor_pqsr = op.GetMutableTensorAtIndex(index_pqsr);
  auto& tensor_qpsr = op.GetMutableTensorAtIndex(index_qpsr);

  // spdlog::info("dims(pqrs) = {} {} {} {}", tensor_pqrs.dim_size(0),
  //              tensor_pqrs.dim_size(1), tensor_pqrs.dim_size(2),
  //              tensor_pqrs.dim_size(3));
  // spdlog::info("dims(qprs) = {} {} {} {}", tensor_qprs.dim_size(0),
  //              tensor_qprs.dim_size(1), tensor_qprs.dim_size(2),
  //              tensor_qprs.dim_size(3));
  // spdlog::info("dims(pqsr) = {} {} {} {}", tensor_pqsr.dim_size(0),
  //              tensor_pqsr.dim_size(1), tensor_pqsr.dim_size(2),
  //              tensor_pqsr.dim_size(3));
  // spdlog::info("dims(qpsr) = {} {} {} {}", tensor_qpsr.dim_size(0),
  //              tensor_qpsr.dim_size(1), tensor_qpsr.dim_size(2),
  //              tensor_qpsr.dim_size(3));

  for (std::size_t s = 0; s < dim_s; s += 1) {
    for (std::size_t r = 0; r < dim_r; r += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          temp_pqrs(p, q, r, s) =
              0.25 *
              (tensor_pqrs(p, q, r, s) + factor_qprs * tensor_qprs(q, p, r, s) +
               factor_pqsr * tensor_pqsr(p, q, s, r) +
               factor_qpsr * tensor_qpsr(q, p, s, r));
        }
      }
    }
  }

  for (std::size_t s = 0; s < dim_s; s += 1) {
    for (std::size_t r = 0; r < dim_r; r += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          tensor_pqrs(p, q, r, s) = temp_pqrs(p, q, r, s);
          tensor_qprs(q, p, r, s) = factor_qprs * temp_pqrs(p, q, r, s);
          tensor_pqsr(p, q, s, r) = factor_pqsr * temp_pqrs(p, q, r, s);
          tensor_qpsr(q, p, s, r) = factor_qpsr * temp_pqrs(p, q, r, s);
        }
      }
    }
  }
}
}  // namespace imsrg
