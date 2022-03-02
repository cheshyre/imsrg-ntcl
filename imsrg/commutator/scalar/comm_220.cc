// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_220.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/quantum_numbers/coupling/factors.h"

namespace imsrg {
// Evaluates scalar [2, 2] -> 0 commutator.
double EvaluateScalar220Commutator(const Scalar2BOperator& a,
                                   const Scalar2BOperator& b) {
  return EvaluateScalar220CommutatorRefImpl(a, b);
}

// Evaluates scalar [2, 2] -> 0 commutator.
double EvaluateScalar220CommutatorRefImpl(const Scalar2BOperator& a,
                                          const Scalar2BOperator& b) {
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());

  const auto& ms_2b = a.GetModelSpace();

  double val = 0.0;

  for (std::size_t chan_a_index = 0; chan_a_index < ms_2b.NumberOfChannels();
       chan_a_index += 1) {
    const auto& chan_a = ms_2b.ChannelAtIndex(chan_a_index);
    const auto jj_2b = chan_a.ChannelKey().OpChannel().JJ();

    imsrg::Scalar2BChannelKey chankey_b(chan_a.ChannelKey().KetChannelKey(),
                                        chan_a.ChannelKey().BraChannelKey(),
                                        jj_2b);
    const auto chan_b_index = ms_2b.IndexOfChannelInModelSpace(chankey_b);

    double factor = 0.25 * imsrg::HatSquared(jj_2b);

    // Tensors
    const auto& tensor_a = a.GetTensorAtIndex(chan_a_index);
    const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);

    // Dims
    const auto dim_p = chan_a.BraChannel1().size();
    const auto dim_q = chan_a.BraChannel2().size();
    const auto dim_r = chan_a.KetChannel1().size();
    const auto dim_s = chan_a.KetChannel2().size();

    // Occs
    const auto& occs_p = chan_a.BraChannel1().ChannelBasis().Occs();
    const auto& occsbar_p = chan_a.BraChannel1().ChannelBasis().OccsBar();
    const auto& occs_q = chan_a.BraChannel2().ChannelBasis().Occs();
    const auto& occsbar_q = chan_a.BraChannel2().ChannelBasis().OccsBar();
    const auto& occs_r = chan_a.KetChannel1().ChannelBasis().Occs();
    const auto& occsbar_r = chan_a.KetChannel1().ChannelBasis().OccsBar();
    const auto& occs_s = chan_a.KetChannel2().ChannelBasis().Occs();
    const auto& occsbar_s = chan_a.KetChannel2().ChannelBasis().OccsBar();

    double interm_val = 0.0;

    for (std::size_t p = 0; p < dim_p; p += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        for (std::size_t r = 0; r < dim_r; r += 1) {
          for (std::size_t s = 0; s < dim_s; s += 1) {
            interm_val += occs_p[p] * occs_q[q] * occsbar_r[r] * occsbar_s[s] *
                          tensor_a(p, q, r, s) * tensor_b(r, s, p, q);
            interm_val -= occsbar_p[p] * occsbar_q[q] * occs_r[r] * occs_s[s] *
                          tensor_a(p, q, r, s) * tensor_b(r, s, p, q);
          }
        }
      }
    }

    val += factor * interm_val;
  }

  return val;
}
}  // namespace imsrg
