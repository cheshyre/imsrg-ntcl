// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_110.h"

#include <vector>

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"
#include "ntcl/data/f_array.h"

#include "imsrg/assert.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/quantum_numbers/coupling/factors.h"

namespace imsrg {

namespace detail {
static ntcl::FArray<double, 2> WeightMatrixElementsWithOccs(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 2>& tensor);
}

double EvaluateScalar110Commutator(const Scalar1BOperator& a,
                                   const Scalar1BOperator& b) {
  // Underlying modelspace should be identical
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());

  if (a.Herm() == b.Herm()) {
    return 0.0;
  }

  const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms = a.GetModelSpace();

  double result = 0.0;
  for (std::size_t chan_index = 0; chan_index < ms.NumberOfChannels();
       chan_index += 1) {
    const auto& chan = ms.ChannelAtIndex(chan_index);
    const auto chan_factor = HatSquared(chan.ChannelKey().OpChannel().JJ());

    const auto& p_occs = chan.BraChannel().ChannelBasis().Occs();
    const auto& p_occsbar = chan.BraChannel().ChannelBasis().OccsBar();
    // q and p channel are the same
    const auto& q_occs = p_occs;
    const auto& q_occsbar = p_occsbar;

    const auto& a_tensor = a.GetTensorAtIndex(chan_index);
    const auto a_tensor_n_p_nbar_q =
        imsrg::detail::WeightMatrixElementsWithOccs(p_occs, q_occsbar,
                                                    a_tensor);
    const auto a_tensor_nbar_p_n_q =
        imsrg::detail::WeightMatrixElementsWithOccs(p_occsbar, q_occs,
                                                    a_tensor);
    const auto& b_tensor = b.GetTensorAtIndex(chan_index);

    result += chan_factor * ntcl_engine.Contract(a_tensor_n_p_nbar_q, b_tensor,
                                                 "C=A(p,q)*B(q,p)", 1.0, 0.0);
    result -= chan_factor * ntcl_engine.Contract(a_tensor_nbar_p_n_q, b_tensor,
                                                 "C=A(p,q)*B(q,p)", 1.0, 0.0);
  }
  return result;
}

// Implements:
// sum_{1b chans} hatsq{chan_jj}
// * (n_p * nbar_q - nbar_p * n_q) * A_{pq} B_{qp}
double EvaluateScalar110CommutatorRefImpl(const Scalar1BOperator& a,
                                          const Scalar1BOperator& b) {
  // Underlying modelspace should be identical
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());

  if (a.Herm() == b.Herm()) {
    return 0.0;
  }

  const auto& ms = a.GetModelSpace();

  double result = 0.0;
  for (std::size_t chan_index = 0; chan_index < ms.NumberOfChannels();
       chan_index += 1) {
    const auto& chan = ms.ChannelAtIndex(chan_index);
    const auto chan_factor = HatSquared(chan.ChannelKey().OpChannel().JJ());
    const auto dim_p = chan.BraChannel().size();
    // q and p channel are the same
    const auto dim_q = dim_p;

    const auto& p_occs = chan.BraChannel().ChannelBasis().Occs();
    const auto& p_occsbar = chan.BraChannel().ChannelBasis().OccsBar();
    const auto& q_occs = p_occs;
    const auto& q_occsbar = p_occsbar;

    const auto& a_tensor = a.GetTensorAtIndex(chan_index);
    const auto& b_tensor = b.GetTensorAtIndex(chan_index);

    double chan_result = 0.0;

    for (std::size_t p = 0; p < dim_p; p += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        chan_result +=
            p_occs[p] * q_occsbar[q] * a_tensor(p, q) * b_tensor(q, p);
        chan_result -=
            p_occsbar[p] * q_occs[q] * a_tensor(p, q) * b_tensor(q, p);
      }
    }

    result += chan_factor * chan_result;
  }
  return result;
}

namespace detail {
ntcl::FArray<double, 2> WeightMatrixElementsWithOccs(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 2>& tensor) {
  Expects(occs_p.size() == tensor.dim_size(0));
  Expects(occs_q.size() == tensor.dim_size(1));

  ntcl::FArray<double, 2> new_tensor(tensor);

  for (std::size_t p = 0; p < occs_p.size(); p += 1) {
    for (std::size_t q = 0; q < occs_q.size(); q += 1) {
      new_tensor(p, q) *= occs_p[p] * occs_q[q];
    }
  }
  return new_tensor;
}
}  // namespace detail
}  // namespace imsrg
