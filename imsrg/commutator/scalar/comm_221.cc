// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_221.h"

#include <vector>

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/quantum_numbers/coupling/factors.h"

namespace imsrg {

namespace detail {
static ntcl::FArray<double, 4> WeightMatrixElementsWithOccs(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const std::vector<double>& occs_r, const ntcl::FArray<double, 4>& tensor);
}

// Evaluates scalar [2, 2] -> 1 commutator.
void EvaluateScalar221Commutator(const Scalar2BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar1BOperator& c) {
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms_1b = c.GetModelSpace();
  const auto& ms_2b = a.GetModelSpace();

  for (std::size_t chan_1rpq_index = 0;
       chan_1rpq_index < ms_2b.NumberOfChannels(); chan_1rpq_index += 1) {
    const auto& chan_1rpq = ms_2b.ChannelAtIndex(chan_1rpq_index);
    const auto jj_2b = chan_1rpq.ChannelKey().OpChannel().JJ();

    const Scalar1BChannelKey chankey_c(chan_1rpq.BraChannel1().ChannelKey(),
                                       chan_1rpq.BraChannel1().ChannelKey());

    const auto chan_c_index = ms_1b.IndexOfChannelInModelSpace(chankey_c);

    double factor_a = 0.5 * imsrg::HatSquared(jj_2b) /
                      imsrg::HatSquared(chankey_c.OpChannel().JJ()) *
                      a.Herm().Factor();
    double factor_b = 0.5 * imsrg::HatSquared(jj_2b) /
                      imsrg::HatSquared(chankey_c.OpChannel().JJ()) *
                      b.Herm().Factor();

    // Tensors
    const auto& tensor_a_1rpq = a.GetTensorAtIndex(chan_1rpq_index);
    const auto& tensor_b_1rpq = b.GetTensorAtIndex(chan_1rpq_index);
    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    // Occs
    const auto& occs_p = chan_1rpq.KetChannel1().ChannelBasis().Occs();
    const auto& occsbar_p = chan_1rpq.KetChannel1().ChannelBasis().OccsBar();
    const auto& occs_q = chan_1rpq.KetChannel2().ChannelBasis().Occs();
    const auto& occsbar_q = chan_1rpq.KetChannel2().ChannelBasis().OccsBar();
    const auto& occs_r = chan_1rpq.BraChannel2().ChannelBasis().Occs();
    const auto& occsbar_r = chan_1rpq.BraChannel2().ChannelBasis().OccsBar();

    // Weighted tensors
    const auto tensor_a_1rpq_n_n_nbar =
        imsrg::detail::WeightMatrixElementsWithOccs(occs_p, occs_q, occsbar_r,
                                                    tensor_a_1rpq);
    const auto tensor_a_1rpq_nbar_nbar_n =
        imsrg::detail::WeightMatrixElementsWithOccs(occsbar_p, occsbar_q,
                                                    occs_r, tensor_a_1rpq);
    const auto tensor_b_1rpq_n_n_nbar =
        imsrg::detail::WeightMatrixElementsWithOccs(occs_p, occs_q, occsbar_r,
                                                    tensor_b_1rpq);
    const auto tensor_b_1rpq_nbar_nbar_n =
        imsrg::detail::WeightMatrixElementsWithOccs(occsbar_p, occsbar_q,
                                                    occs_r, tensor_b_1rpq);

    ntcl_engine.Contract(tensor_c, tensor_a_1rpq_nbar_nbar_n, tensor_b_1rpq,
                         "C(i,j)=A(i,r,p,q)*B(j,r,p,q)", factor_b, 1.0);
    ntcl_engine.Contract(tensor_c, tensor_a_1rpq_n_n_nbar, tensor_b_1rpq,
                         "C(i,j)=A(i,r,p,q)*B(j,r,p,q)", factor_b, 1.0);
    ntcl_engine.Contract(tensor_c, tensor_b_1rpq_nbar_nbar_n, tensor_a_1rpq,
                         "C(i,j)=A(i,r,p,q)*B(j,r,p,q)", -1 * factor_a, 1.0);
    ntcl_engine.Contract(tensor_c, tensor_b_1rpq_n_n_nbar, tensor_a_1rpq,
                         "C(i,j)=A(i,r,p,q)*B(j,r,p,q)", -1 * factor_a, 1.0);
  }
}

// Evaluates scalar [2, 2] -> 1 commutator.
void EvaluateScalar221CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar1BOperator& c) {
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ms_1b = c.GetModelSpace();
  const auto& ms_2b = a.GetModelSpace();

  for (std::size_t chan_1rpq_index = 0;
       chan_1rpq_index < ms_2b.NumberOfChannels(); chan_1rpq_index += 1) {
    const auto& chan_1rpq = ms_2b.ChannelAtIndex(chan_1rpq_index);
    const auto jj_2b = chan_1rpq.ChannelKey().OpChannel().JJ();

    imsrg::Scalar2BChannelKey chankey_pq2r(
        chan_1rpq.ChannelKey().KetChannelKey(),
        chan_1rpq.ChannelKey().BraChannelKey(), jj_2b);

    const auto chan_pq2r_index = ms_2b.IndexOfChannelInModelSpace(chankey_pq2r);

    const Scalar1BChannelKey chankey_c(chan_1rpq.BraChannel1().ChannelKey(),
                                       chan_1rpq.BraChannel1().ChannelKey());

    const auto chan_c_index = ms_1b.IndexOfChannelInModelSpace(chankey_c);

    double factor = 0.5 * imsrg::HatSquared(jj_2b) /
                    imsrg::HatSquared(chankey_c.OpChannel().JJ());

    // Tensors
    const auto& tensor_a_1rpq = a.GetTensorAtIndex(chan_1rpq_index);
    const auto& tensor_b_1rpq = b.GetTensorAtIndex(chan_1rpq_index);
    const auto& tensor_a_pq2r = a.GetTensorAtIndex(chan_pq2r_index);
    const auto& tensor_b_pq2r = b.GetTensorAtIndex(chan_pq2r_index);
    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    // Occs
    const auto& occs_p = chan_1rpq.KetChannel1().ChannelBasis().Occs();
    const auto& occsbar_p = chan_1rpq.KetChannel1().ChannelBasis().OccsBar();
    const auto& occs_q = chan_1rpq.KetChannel2().ChannelBasis().Occs();
    const auto& occsbar_q = chan_1rpq.KetChannel2().ChannelBasis().OccsBar();
    const auto& occs_r = chan_1rpq.BraChannel2().ChannelBasis().Occs();
    const auto& occsbar_r = chan_1rpq.BraChannel2().ChannelBasis().OccsBar();

    // Dims
    const auto dim_1 = chan_1rpq.BraChannel1().size();
    const auto dim_2 = chan_1rpq.BraChannel1().size();
    const auto dim_r = chan_1rpq.BraChannel2().size();
    const auto dim_p = chan_1rpq.KetChannel1().size();
    const auto dim_q = chan_1rpq.KetChannel2().size();

    for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
      for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          for (std::size_t q = 0; q < dim_q; q += 1) {
            for (std::size_t r = 0; r < dim_r; r += 1) {
              tensor_c(i1, i2) += factor * occsbar_p[p] * occsbar_q[q] *
                                  occs_r[r] * tensor_a_1rpq(i1, r, p, q) *
                                  tensor_b_pq2r(p, q, i2, r);
              tensor_c(i1, i2) += factor * occs_p[p] * occs_q[q] *
                                  occsbar_r[r] * tensor_a_1rpq(i1, r, p, q) *
                                  tensor_b_pq2r(p, q, i2, r);
              tensor_c(i1, i2) -= factor * occsbar_p[p] * occsbar_q[q] *
                                  occs_r[r] * tensor_b_1rpq(i1, r, p, q) *
                                  tensor_a_pq2r(p, q, i2, r);
              tensor_c(i1, i2) -= factor * occs_p[p] * occs_q[q] *
                                  occsbar_r[r] * tensor_b_1rpq(i1, r, p, q) *
                                  tensor_a_pq2r(p, q, i2, r);
            }
          }
        }
      }
    }
  }
}

namespace detail {
ntcl::FArray<double, 4> WeightMatrixElementsWithOccs(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const std::vector<double>& occs_r, const ntcl::FArray<double, 4>& tensor) {
  Expects(occs_p.size() == tensor.dim_size(2));
  Expects(occs_q.size() == tensor.dim_size(3));
  Expects(occs_r.size() == tensor.dim_size(1));

  ntcl::FArray<double, 4> new_tensor(tensor);

  for (std::size_t i1 = 0; i1 < tensor.dim_size(0); i1 += 1) {
    for (std::size_t r = 0; r < occs_r.size(); r += 1) {
      for (std::size_t p = 0; p < occs_p.size(); p += 1) {
        for (std::size_t q = 0; q < occs_q.size(); q += 1) {
          new_tensor(i1, r, p, q) *= occs_p[p] * occs_q[q] * occs_r[r];
        }
      }
    }
  }
  return new_tensor;
}
}  // namespace detail
}  // namespace imsrg
