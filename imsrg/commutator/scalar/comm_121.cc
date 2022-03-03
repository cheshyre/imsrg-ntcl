// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_121.h"

#include <algorithm>
#include <vector>

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"
#include "ntcl/data/f_array.h"

#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/coupling/factors.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {

static ntcl::FArray<double, 2> WeightMatrixElementsWithOccs(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 2>& tensor);

static void EvaluateScalar121CommutatorWithFactorOld(const Scalar1BOperator& a,
                                                     const Scalar2BOperator& b,
                                                     Scalar1BOperator& c,
                                                     int factor);

static void EvaluateScalar121CommutatorWithFactor(const Scalar1BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar1BOperator& c,
                                                  int factor);

static void EvaluateScalar121CommutatorRefImplWithFactor(
    const Scalar1BOperator& a, const Scalar2BOperator& b, Scalar1BOperator& c,
    int factor);

static void EvaluateScalar121CommutatorRefImplWithFactorOld(
    const Scalar1BOperator& a, const Scalar2BOperator& b, Scalar1BOperator& c,
    int factor);

}  // namespace detail

void EvaluateScalar121Commutator(const Scalar1BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar1BOperator& c) {
  imsrg::detail::EvaluateScalar121CommutatorWithFactor(a, b, c, 1);
}

void EvaluateScalar121CommutatorRefImpl(const Scalar1BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar1BOperator& c) {
  imsrg::detail::EvaluateScalar121CommutatorRefImplWithFactor(a, b, c, 1);
}

// Evaluates scalar [2, 1] -> 1 commutator.
void EvaluateScalar211Commutator(const Scalar2BOperator& a,
                                 const Scalar1BOperator& b,
                                 Scalar1BOperator& c) {
  imsrg::detail::EvaluateScalar121CommutatorWithFactor(b, a, c, -1);
}

// Evaluates scalar [2, 1] -> 1 commutator.
void EvaluateScalar211CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar1BOperator& b,
                                        Scalar1BOperator& c) {
  imsrg::detail::EvaluateScalar121CommutatorRefImplWithFactor(b, a, c, -1);
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

void EvaluateScalar121CommutatorWithFactorOld(const Scalar1BOperator& a,
                                              const Scalar2BOperator& b,
                                              Scalar1BOperator& c, int factor) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_b_index = 0; chan_b_index < ms_2b.NumberOfChannels();
       chan_b_index += 1) {
    const auto& chan_b = ms_2b.ChannelAtIndex(chan_b_index);
    const auto& chan_1 = chan_b.BraChannel1();
    const auto& chan_q = chan_b.BraChannel2();
    const auto& chan_2 = chan_b.KetChannel1();
    const auto& chan_p = chan_b.KetChannel2();

    if (chan_1.ChannelKey() != chan_2.ChannelKey()) {
      continue;
    }

    if (chan_p.ChannelKey() != chan_q.ChannelKey()) {
      continue;
    }

    // Derived channels
    const imsrg::Scalar1BChannelKey chankey_a(chan_p.ChannelKey(),
                                              chan_q.ChannelKey());
    if (!ms_1b.IsChannelInModelSpace(chankey_a)) {
      continue;
    }
    const auto chan_a_index = ms_1b.IndexOfChannelInModelSpace(chankey_a);

    const imsrg::Scalar1BChannelKey chankey_c(chan_1.ChannelKey(),
                                              chan_2.ChannelKey());
    if (!ms_1b.IsChannelInModelSpace(chankey_c)) {
      continue;
    }
    const auto chan_c_index = ms_1b.IndexOfChannelInModelSpace(chankey_c);

    double channel_factor =
        (1.0 * factor *
         imsrg::HatSquared(chan_b.ChannelKey().OpChannel().JJ())) /
        imsrg::HatSquared(chankey_c.OpChannel().JJ());

    // Tensors
    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);
    const auto& tensor_a = a.GetTensorAtIndex(chan_a_index);
    const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);

    // Occs
    const auto& occs_p = chan_p.ChannelBasis().Occs();
    const auto& occsbar_p = chan_p.ChannelBasis().OccsBar();
    const auto& occs_q = chan_q.ChannelBasis().Occs();
    const auto& occsbar_q = chan_q.ChannelBasis().OccsBar();

    const auto tensor_a_occs_occsbar =
        WeightMatrixElementsWithOccs(occs_p, occsbar_q, tensor_a);
    const auto tensor_a_occsbar_occs =
        WeightMatrixElementsWithOccs(occsbar_p, occs_q, tensor_a);

    ntcl_engine.Contract(tensor_c, tensor_a_occs_occsbar, tensor_b,
                         "C(i,j)=A(p,q)*B(i,q,j,p)", channel_factor, 1.0);
    ntcl_engine.Contract(tensor_c, tensor_a_occsbar_occs, tensor_b,
                         "C(i,j)=A(p,q)*B(i,q,j,p)", -1 * channel_factor, 1.0);
  }
}

void EvaluateScalar121CommutatorWithFactor(const Scalar1BOperator& a,
                                           const Scalar2BOperator& b,
                                           Scalar1BOperator& c, int factor) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_c_index = 0; chan_c_index < ms_1b.NumberOfChannels();
       chan_c_index += 1) {
    const auto& chan_c = ms_1b.ChannelAtIndex(chan_c_index);
    const auto& chan_1 = chan_c.BraChannel();
    const auto& chan_2 = chan_c.KetChannel();

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    double channel_factor1 =
        (1.0 * factor) /
        imsrg::HatSquared(chan_c.ChannelKey().OpChannel().JJ());

    for (std::size_t chan_a_index = 0; chan_a_index < ms_1b.NumberOfChannels();
         chan_a_index += 1) {
      const auto& chan_a = ms_1b.ChannelAtIndex(chan_a_index);
      const auto& chan_p = chan_a.BraChannel();
      const auto& chan_q = chan_a.KetChannel();

      const auto& tensor_a = a.GetTensorAtIndex(chan_a_index);

      // Occs
      const auto& occs_p = chan_p.ChannelBasis().Occs();
      const auto& occsbar_p = chan_p.ChannelBasis().OccsBar();
      const auto& occs_q = chan_q.ChannelBasis().Occs();
      const auto& occsbar_q = chan_q.ChannelBasis().OccsBar();

      const auto tensor_a_occs_occsbar =
          WeightMatrixElementsWithOccs(occs_p, occsbar_q, tensor_a);
      const auto tensor_a_occsbar_occs =
          WeightMatrixElementsWithOccs(occsbar_p, occs_q, tensor_a);

      // B_1q2p
      const auto jj_1q_min =
          imsrg::CouplingMinimum<imsrg::TotalAngMom>(chan_1.JJ(), chan_q.JJ());
      const auto jj_1q_max =
          imsrg::CouplingMaximum<imsrg::TotalAngMom>(chan_1.JJ(), chan_q.JJ());
      const auto jj_2p_min =
          imsrg::CouplingMinimum<imsrg::TotalAngMom>(chan_2.JJ(), chan_p.JJ());
      const auto jj_2p_max =
          imsrg::CouplingMaximum<imsrg::TotalAngMom>(chan_2.JJ(), chan_p.JJ());

      const auto jj_b_range =
          imsrg::CouplingRangeFromMinAndMax<imsrg::TotalAngMom>(
              std::max(jj_1q_min, jj_2p_min), std::min(jj_1q_max, jj_2p_max));

      for (const auto jj_b : jj_b_range) {
        const auto channel_factor2 = HatSquared(jj_b);
        imsrg::Scalar2BChannelKey chankey_b(
            {chan_1.ChannelKey(), chan_q.ChannelKey()},
            {chan_2.ChannelKey(), chan_p.ChannelKey()}, jj_b);
        if (!ms_2b.IsChannelInModelSpace(chankey_b)) {
          continue;
        }
        const auto chan_b_index = ms_2b.IndexOfChannelInModelSpace(chankey_b);
        const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);

        ntcl_engine.Contract(tensor_c, tensor_a_occs_occsbar, tensor_b,
                             "C(i,j)=A(p,q)*B(i,q,j,p)",
                             channel_factor1 * channel_factor2, 1.0);
        ntcl_engine.Contract(tensor_c, tensor_a_occsbar_occs, tensor_b,
                             "C(i,j)=A(p,q)*B(i,q,j,p)",
                             -1 * channel_factor1 * channel_factor2, 1.0);
      }
    }
  }
}

void EvaluateScalar121CommutatorRefImplWithFactorOld(const Scalar1BOperator& a,
                                                     const Scalar2BOperator& b,
                                                     Scalar1BOperator& c,
                                                     int factor) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_b_index = 0; chan_b_index < ms_2b.NumberOfChannels();
       chan_b_index += 1) {
    const auto& chan_b = ms_2b.ChannelAtIndex(chan_b_index);
    const auto& chan_1 = chan_b.BraChannel1();
    const auto& chan_q = chan_b.BraChannel2();
    const auto& chan_2 = chan_b.KetChannel1();
    const auto& chan_p = chan_b.KetChannel2();

    if (chan_1.ChannelKey() != chan_2.ChannelKey()) {
      continue;
    }

    if (chan_p.ChannelKey() != chan_q.ChannelKey()) {
      continue;
    }

    // Derived channels
    const imsrg::Scalar1BChannelKey chankey_a(chan_p.ChannelKey(),
                                              chan_q.ChannelKey());
    if (!ms_1b.IsChannelInModelSpace(chankey_a)) {
      continue;
    }
    const auto chan_a_index = ms_1b.IndexOfChannelInModelSpace(chankey_a);

    const imsrg::Scalar1BChannelKey chankey_c(chan_1.ChannelKey(),
                                              chan_2.ChannelKey());
    if (!ms_1b.IsChannelInModelSpace(chankey_c)) {
      continue;
    }
    const auto chan_c_index = ms_1b.IndexOfChannelInModelSpace(chankey_c);

    double channel_factor =
        (1.0 * factor *
         imsrg::HatSquared(chan_b.ChannelKey().OpChannel().JJ())) /
        imsrg::HatSquared(chankey_c.OpChannel().JJ());

    // Tensors
    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);
    const auto& tensor_a = a.GetTensorAtIndex(chan_a_index);
    const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);

    // Dims
    const auto dim_p = chan_p.size();
    const auto dim_q = chan_q.size();
    const auto dim_1 = chan_1.size();
    const auto dim_2 = chan_2.size();

    // Occs
    const auto& occs_p = chan_p.ChannelBasis().Occs();
    const auto& occsbar_p = chan_p.ChannelBasis().OccsBar();
    const auto& occs_q = chan_q.ChannelBasis().Occs();
    const auto& occsbar_q = chan_q.ChannelBasis().OccsBar();

    for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
      for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t p = 0; p < dim_p; p += 1) {
            tensor_c(i1, i2) += channel_factor * occs_p[p] * occsbar_q[q] *
                                tensor_a(p, q) * tensor_b(i1, q, i2, p);
            tensor_c(i1, i2) -= channel_factor * occsbar_p[p] * occs_q[q] *
                                tensor_a(p, q) * tensor_b(i1, q, i2, p);
          }
        }
      }
    }
  }
}

void EvaluateScalar121CommutatorRefImplWithFactor(const Scalar1BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar1BOperator& c,
                                                  int factor) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_c_index = 0; chan_c_index < ms_1b.NumberOfChannels();
       chan_c_index += 1) {
    const auto& chan_c = ms_1b.ChannelAtIndex(chan_c_index);
    const auto& chan_1 = chan_c.BraChannel();
    const auto& chan_2 = chan_c.KetChannel();

    const auto dim_1 = chan_1.size();
    const auto dim_2 = chan_2.size();

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    double channel_factor1 =
        (1.0 * factor) /
        imsrg::HatSquared(chan_c.ChannelKey().OpChannel().JJ());

    for (std::size_t chan_a_index = 0; chan_a_index < ms_1b.NumberOfChannels();
         chan_a_index += 1) {
      const auto& chan_a = ms_1b.ChannelAtIndex(chan_a_index);
      const auto& chan_p = chan_a.BraChannel();
      const auto& chan_q = chan_a.KetChannel();

      const auto dim_p = chan_p.size();
      const auto dim_q = chan_q.size();

      const auto& tensor_a = a.GetTensorAtIndex(chan_a_index);

      // Occs
      const auto& occs_p = chan_p.ChannelBasis().Occs();
      const auto& occsbar_p = chan_p.ChannelBasis().OccsBar();
      const auto& occs_q = chan_q.ChannelBasis().Occs();
      const auto& occsbar_q = chan_q.ChannelBasis().OccsBar();

      // B_1q2p
      const auto jj_1q_min =
          imsrg::CouplingMinimum<imsrg::TotalAngMom>(chan_1.JJ(), chan_q.JJ());
      const auto jj_1q_max =
          imsrg::CouplingMaximum<imsrg::TotalAngMom>(chan_1.JJ(), chan_q.JJ());
      const auto jj_2p_min =
          imsrg::CouplingMinimum<imsrg::TotalAngMom>(chan_2.JJ(), chan_p.JJ());
      const auto jj_2p_max =
          imsrg::CouplingMaximum<imsrg::TotalAngMom>(chan_2.JJ(), chan_p.JJ());

      const auto jj_b_range =
          imsrg::CouplingRangeFromMinAndMax<imsrg::TotalAngMom>(
              std::max(jj_1q_min, jj_2p_min), std::min(jj_1q_max, jj_2p_max));

      for (const auto jj_b : jj_b_range) {
        const auto channel_factor2 = HatSquared(jj_b);
        imsrg::Scalar2BChannelKey chankey_b(
            {chan_1.ChannelKey(), chan_q.ChannelKey()},
            {chan_2.ChannelKey(), chan_p.ChannelKey()}, jj_b);
        if (!ms_2b.IsChannelInModelSpace(chankey_b)) {
          continue;
        }
        const auto chan_b_index = ms_2b.IndexOfChannelInModelSpace(chankey_b);
        const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);
        for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
          for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
            for (std::size_t q = 0; q < dim_q; q += 1) {
              for (std::size_t p = 0; p < dim_p; p += 1) {
                tensor_c(i1, i2) += channel_factor1 * channel_factor2 *
                                    occs_p[p] * occsbar_q[q] * tensor_a(p, q) *
                                    tensor_b(i1, q, i2, p);
                tensor_c(i1, i2) -= channel_factor1 * channel_factor2 *
                                    occsbar_p[p] * occs_q[q] * tensor_a(p, q) *
                                    tensor_b(i1, q, i2, p);
              }
            }
          }
        }
      }
    }
  }
}

}  // namespace detail
}  // namespace imsrg
