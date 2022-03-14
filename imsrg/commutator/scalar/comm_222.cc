// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_222.h"

#include <vector>

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"
#include "ntcl/data/f_array.h"

#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/openmp_runtime.h"
#include "imsrg/operator/scalar/two_body/antisymmetry.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/quantum_numbers/coupling/wigner_symbols.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

namespace detail {

static void EvaluateScalar222CommutatorDirectTermNTCLImpl(
    const Scalar2BOperator& a, const Scalar2BOperator& b, Scalar2BOperator& c);

static void EvaluateScalar222CommutatorDirectTermRefImpl(
    const Scalar2BOperator& a, const Scalar2BOperator& b, Scalar2BOperator& c);

static void EvaluateScalar222CommutatorPandyaTermRefImpl(
    const Scalar2BOperator& a, const Scalar2BOperator& b, Scalar2BOperator& c);

static void Scalar222CommutatorDirectTermRefImplCore(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 4>& tensor_pq12,
    const ntcl::FArray<double, 4>& tensor_pq34,
    ntcl::FArray<double, 4>& tensor_1234, double factor = 1.0);

static void Scalar222CommutatorDirectTermRefImplCorePreweighted(
    const ntcl::FArray<double, 4>& tensor_pq12,
    const ntcl::FArray<double, 4>& tensor_pq34,
    ntcl::FArray<double, 4>& tensor_1234, double factor = 1.0);

static ntcl::FArray<double, 4> WeightTensorWithOccupations(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 4>& tensor_pq12);
}  // namespace detail

void EvaluateScalar222Commutator(const Scalar2BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar222CommutatorDirectTermNTCLImpl(a, b, c);
  imsrg::detail::EvaluateScalar222CommutatorPandyaTermRefImpl(a, b, c);
}

// Evaluates scalar [2, 2] -> 2 commutator.
void EvaluateScalar222CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar222CommutatorDirectTermRefImpl(a, b, c);
  imsrg::detail::EvaluateScalar222CommutatorPandyaTermRefImpl(a, b, c);
}

namespace detail {

void EvaluateScalar222CommutatorDirectTermNTCLImpl(const Scalar2BOperator& a,
                                                   const Scalar2BOperator& b,
                                                   Scalar2BOperator& c) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(b.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  if (!imsrg::OpenMPRuntime::IsInitialized()) {
    imsrg::OpenMPRuntime::InitializeRuntime();
  }

  // const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms_2b = a.GetModelSpace();

  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    const auto chankey_c = ms_2b.ChannelAtIndex(chan_c_index).ChannelKey();
    const auto op_chan = chankey_c.OpChannel();
    const auto state_chankey_12 = chankey_c.BraChannelKey();
    const auto state_chankey_34 = chankey_c.KetChannelKey();

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    const auto& state_chankeys_pq =
        ms_2b.GetStateChannelsInOperatorChannel(op_chan);

    for (const auto& state_chankey_pq : state_chankeys_pq) {
      const imsrg::Scalar2BChannelKey chankey_pq12(
          state_chankey_pq, state_chankey_12, op_chan.JJ());
      const imsrg::Scalar2BChannelKey chankey_pq34(
          state_chankey_pq, state_chankey_34, op_chan.JJ());

      const auto chan_pq12_index =
          ms_2b.IndexOfChannelInModelSpace(chankey_pq12);
      const auto chan_pq34_index =
          ms_2b.IndexOfChannelInModelSpace(chankey_pq34);

      // Occs
      const auto& occs_p = ms_2b.ChannelAtIndex(chan_pq12_index)
                               .BraChannel1()
                               .ChannelBasis()
                               .Occs();
      const auto& occsbar_p = ms_2b.ChannelAtIndex(chan_pq12_index)
                                  .BraChannel1()
                                  .ChannelBasis()
                                  .OccsBar();
      const auto& occs_q = ms_2b.ChannelAtIndex(chan_pq12_index)
                               .BraChannel2()
                               .ChannelBasis()
                               .Occs();
      const auto& occsbar_q = ms_2b.ChannelAtIndex(chan_pq12_index)
                                  .BraChannel2()
                                  .ChannelBasis()
                                  .OccsBar();

      // Tensors
      const auto& tensor_a_pq12 = a.GetTensorAtIndex(chan_pq12_index);
      const auto& tensor_a_pq34 = a.GetTensorAtIndex(chan_pq34_index);
      const auto& tensor_b_pq12 = b.GetTensorAtIndex(chan_pq12_index);
      const auto& tensor_b_pq34 = b.GetTensorAtIndex(chan_pq34_index);

      const auto tensor_a_pq12_nbar_nbar =
          WeightTensorWithOccupations(occsbar_p, occsbar_q, tensor_a_pq12);
      const auto tensor_b_pq12_nbar_nbar =
          WeightTensorWithOccupations(occsbar_p, occsbar_q, tensor_b_pq12);
      const auto tensor_a_pq12_n_n =
          WeightTensorWithOccupations(occs_p, occs_q, tensor_a_pq12);
      const auto tensor_b_pq12_n_n =
          WeightTensorWithOccupations(occs_p, occs_q, tensor_b_pq12);

      Scalar222CommutatorDirectTermRefImplCorePreweighted(
          tensor_a_pq12_nbar_nbar, tensor_b_pq34, tensor_c,
          0.5 * a.Herm().Factor());
      // For some reason the following NTCL call does not work
      // I need to debug this in a simpler setting
      // For now we rely on a loop based implementation
      // ntcl_engine.Contract(tensor_c, tensor_a_pq12_nbar_nbar, tensor_b_pq34,
      //                      "C(i,j,k,l)=A(p,q,i,j)*B(p,q,k,l)",
      //                      0.5 * a.Herm().Factor(), 1.0);
      Scalar222CommutatorDirectTermRefImplCorePreweighted(
          tensor_b_pq12_nbar_nbar, tensor_a_pq34, tensor_c,
          -0.5 * b.Herm().Factor());
      Scalar222CommutatorDirectTermRefImplCorePreweighted(
          tensor_a_pq12_n_n, tensor_b_pq34, tensor_c, -0.5 * a.Herm().Factor());
      Scalar222CommutatorDirectTermRefImplCorePreweighted(
          tensor_b_pq12_n_n, tensor_a_pq34, tensor_c, 0.5 * b.Herm().Factor());
    }
  }
}

void EvaluateScalar222CommutatorDirectTermRefImpl(const Scalar2BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar2BOperator& c) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(b.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  if (!imsrg::OpenMPRuntime::IsInitialized()) {
    imsrg::OpenMPRuntime::InitializeRuntime();
  }

  const auto& ms_2b = a.GetModelSpace();

#pragma omp parallel for schedule(dynamic, 100)
  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    const auto chankey_c = ms_2b.ChannelAtIndex(chan_c_index).ChannelKey();
    const auto op_chan = chankey_c.OpChannel();
    const auto state_chankey_12 = chankey_c.BraChannelKey();
    const auto state_chankey_34 = chankey_c.KetChannelKey();

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);

    const auto& state_chankeys_pq =
        ms_2b.GetStateChannelsInOperatorChannel(op_chan);

    for (const auto& state_chankey_pq : state_chankeys_pq) {
      const imsrg::Scalar2BChannelKey chankey_pq12(
          state_chankey_pq, state_chankey_12, op_chan.JJ());
      const imsrg::Scalar2BChannelKey chankey_pq34(
          state_chankey_pq, state_chankey_34, op_chan.JJ());

      const auto chan_pq12_index =
          ms_2b.IndexOfChannelInModelSpace(chankey_pq12);
      const auto chan_pq34_index =
          ms_2b.IndexOfChannelInModelSpace(chankey_pq34);

      // Occs
      const auto& occs_p = ms_2b.ChannelAtIndex(chan_pq12_index)
                               .BraChannel1()
                               .ChannelBasis()
                               .Occs();
      const auto& occsbar_p = ms_2b.ChannelAtIndex(chan_pq12_index)
                                  .BraChannel1()
                                  .ChannelBasis()
                                  .OccsBar();
      const auto& occs_q = ms_2b.ChannelAtIndex(chan_pq12_index)
                               .BraChannel2()
                               .ChannelBasis()
                               .Occs();
      const auto& occsbar_q = ms_2b.ChannelAtIndex(chan_pq12_index)
                                  .BraChannel2()
                                  .ChannelBasis()
                                  .OccsBar();

      // Tensors
      const auto& tensor_a_pq12 = a.GetTensorAtIndex(chan_pq12_index);
      const auto& tensor_a_pq34 = a.GetTensorAtIndex(chan_pq34_index);
      const auto& tensor_b_pq12 = b.GetTensorAtIndex(chan_pq12_index);
      const auto& tensor_b_pq34 = b.GetTensorAtIndex(chan_pq34_index);

      Scalar222CommutatorDirectTermRefImplCore(
          occsbar_p, occsbar_q, tensor_a_pq12, tensor_b_pq34, tensor_c,
          0.5 * a.Herm().Factor());
      Scalar222CommutatorDirectTermRefImplCore(
          occsbar_p, occsbar_q, tensor_b_pq12, tensor_a_pq34, tensor_c,
          -0.5 * b.Herm().Factor());
      Scalar222CommutatorDirectTermRefImplCore(occs_p, occs_q, tensor_a_pq12,
                                               tensor_b_pq34, tensor_c,
                                               -0.5 * a.Herm().Factor());
      Scalar222CommutatorDirectTermRefImplCore(occs_p, occs_q, tensor_b_pq12,
                                               tensor_a_pq34, tensor_c,
                                               0.5 * b.Herm().Factor());
    }
  }
}

void EvaluateScalar222CommutatorPandyaTermRefImpl(const Scalar2BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar2BOperator& c) {
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(b.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  if (!imsrg::OpenMPRuntime::IsInitialized()) {
    imsrg::OpenMPRuntime::InitializeRuntime();
  }
  imsrg::WignerSymbolEngine::GetInstance();

  const auto& ms_2b = a.GetModelSpace();
  const auto& sp_ms = ms_2b.SingleParticleModelSpace();
  const auto& bare_channels = ms_2b.BareChannels();

  const int factor = 4 * b.Herm().Factor();

#pragma omp parallel for schedule(dynamic, 100)
  for (std::size_t i = 0; i < bare_channels.size(); i += 1) {
    const auto pandya_bare_chan =
        imsrg::BareChannelKeyPandyaSwap(bare_channels[i]);

    const auto [chan_1, chan_4, chan_3, chan_2] = pandya_bare_chan;
    const auto dim_1 = sp_ms.ChannelDim(chan_1);
    const auto dim_2 = sp_ms.ChannelDim(chan_2);
    const auto dim_3 = sp_ms.ChannelDim(chan_3);
    const auto dim_4 = sp_ms.ChannelDim(chan_4);

    const auto pandya_chans = imsrg::GeneratePandyaChannels(pandya_bare_chan);
    for (const auto pandya_chan : pandya_chans) {
      ntcl::FArray<double, 4> tensor_c(dim_1, dim_4, dim_3, dim_2);

      const auto op_chan = pandya_chan.OperatorChannel();

      const auto& state_chankeys_pq =
          ms_2b.GetStateChannelsInPandyaOperatorChannel(op_chan);

      for (const auto [chan_p, chan_q] : state_chankeys_pq) {
        const auto& occs_p = sp_ms.Occs(chan_p);
        const auto& occsbar_p = sp_ms.OccsBar(chan_p);
        const auto& occs_q = sp_ms.Occs(chan_q);
        const auto& occsbar_q = sp_ms.OccsBar(chan_q);

        const auto dim_p = occs_p.size();
        const auto dim_q = occs_q.size();

        Scalar2BPandyaChannelKey a_chankey({chan_p, chan_q, chan_3, chan_2},
                                           op_chan.JJ());
        Scalar2BPandyaChannelKey b_chankey({chan_p, chan_q, chan_1, chan_4},
                                           op_chan.JJ());

        const auto tensor_a = a.GeneratePandyaTensorInPandyaChannel(a_chankey);
        const auto tensor_b = b.GeneratePandyaTensorInPandyaChannel(b_chankey);

        for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
          for (std::size_t i3 = 0; i3 < dim_3; i3 += 1) {
            for (std::size_t i4 = 0; i4 < dim_4; i4 += 1) {
              for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
                double sum_val = 0.0;
                for (std::size_t q = 0; q < dim_q; q += 1) {
                  for (std::size_t p = 0; p < dim_p; p += 1) {
                    sum_val += tensor_a(p, q, i3, i2) * tensor_b(p, q, i1, i4) *
                               occs_p[p] * occsbar_q[q];
                    sum_val -= tensor_a(p, q, i3, i2) * tensor_b(p, q, i1, i4) *
                               occsbar_p[p] * occs_q[q];
                  }
                }
                tensor_c(i1, i4, i3, i2) += sum_val;
              }
            }
          }
        }
      }

      c.AddPandyaTensor(pandya_chan, tensor_c, factor);
    }
  }

  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    const auto chankey_c = ms_2b.ChannelAtIndex(chan_c_index).ChannelKey();

    imsrg::AntisymmetrizeOperatorInChannel(c, chankey_c);
  }
}

void Scalar222CommutatorDirectTermRefImplCore(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 4>& tensor_pq12,
    const ntcl::FArray<double, 4>& tensor_pq34,
    ntcl::FArray<double, 4>& tensor_1234, double factor) {
  const auto dim_i1 = tensor_1234.dim_size(0);
  const auto dim_i2 = tensor_1234.dim_size(1);
  const auto dim_i3 = tensor_1234.dim_size(2);
  const auto dim_i4 = tensor_1234.dim_size(3);
  const auto dim_p = occs_p.size();
  const auto dim_q = occs_q.size();

  for (std::size_t i4 = 0; i4 < dim_i4; i4 += 1) {
    for (std::size_t i3 = 0; i3 < dim_i3; i3 += 1) {
      for (std::size_t i2 = 0; i2 < dim_i2; i2 += 1) {
        for (std::size_t i1 = 0; i1 < dim_i1; i1 += 1) {
          double sum_val = 0.0;
          for (std::size_t q = 0; q < dim_q; q += 1) {
            for (std::size_t p = 0; p < dim_p; p += 1) {
              sum_val += occs_p[p] * occs_q[q] * tensor_pq12(p, q, i1, i2) *
                         tensor_pq34(p, q, i3, i4);
            }
          }
          tensor_1234(i1, i2, i3, i4) += factor * sum_val;
        }
      }
    }
  }
}

void Scalar222CommutatorDirectTermRefImplCorePreweighted(
    const ntcl::FArray<double, 4>& tensor_pq12,
    const ntcl::FArray<double, 4>& tensor_pq34,
    ntcl::FArray<double, 4>& tensor_1234, double factor) {
  const auto dim_i1 = tensor_1234.dim_size(0);
  const auto dim_i2 = tensor_1234.dim_size(1);
  const auto dim_i3 = tensor_1234.dim_size(2);
  const auto dim_i4 = tensor_1234.dim_size(3);
  const auto dim_p = tensor_pq12.dim_size(0);
  const auto dim_q = tensor_pq12.dim_size(1);

  for (std::size_t i4 = 0; i4 < dim_i4; i4 += 1) {
    for (std::size_t i3 = 0; i3 < dim_i3; i3 += 1) {
      for (std::size_t i2 = 0; i2 < dim_i2; i2 += 1) {
        for (std::size_t i1 = 0; i1 < dim_i1; i1 += 1) {
          double sum_val = 0.0;
          for (std::size_t q = 0; q < dim_q; q += 1) {
            for (std::size_t p = 0; p < dim_p; p += 1) {
              sum_val += tensor_pq12(p, q, i1, i2) * tensor_pq34(p, q, i3, i4);
            }
          }
          tensor_1234(i1, i2, i3, i4) += factor * sum_val;
        }
      }
    }
  }
}

ntcl::FArray<double, 4> WeightTensorWithOccupations(
    const std::vector<double>& occs_p, const std::vector<double>& occs_q,
    const ntcl::FArray<double, 4>& tensor_pq12) {
  const auto dim_i1 = tensor_pq12.dim_size(2);
  const auto dim_i2 = tensor_pq12.dim_size(3);
  const auto dim_p = occs_p.size();
  const auto dim_q = occs_q.size();

  ntcl::FArray<double, 4> out(dim_p, dim_q, dim_i1, dim_i2);

  for (std::size_t i2 = 0; i2 < dim_i2; i2 += 1) {
    for (std::size_t i1 = 0; i1 < dim_i1; i1 += 1) {
      for (std::size_t q = 0; q < dim_q; q += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          out(p, q, i1, i2) = tensor_pq12(p, q, i1, i2) * occs_p[p] * occs_q[q];
        }
      }
    }
  }
  return out;
}
}  // namespace detail
}  // namespace imsrg
