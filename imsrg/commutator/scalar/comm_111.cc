// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_111.h"

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"
#include "ntcl/data/f_array.h"

#include "imsrg/assert.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/quantum_numbers/coupling/factors.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

void EvaluateScalar111Commutator(const Scalar1BOperator& a,
                                 const Scalar1BOperator& b,
                                 Scalar1BOperator& c) {
  // Underlying modelspace should be identical
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms = a.GetModelSpace();

  for (std::size_t chan_index = 0; chan_index < ms.NumberOfChannels();
       chan_index += 1) {
    auto& c_tensor = c.GetMutableTensorAtIndex(chan_index);
    const auto& a_tensor = a.GetTensorAtIndex(chan_index);
    const auto& b_tensor = b.GetTensorAtIndex(chan_index);

    ntcl_engine.Contract(c_tensor, a_tensor, b_tensor, "C(i,j)=A(i,p)*B(p,j)",
                         1.0, 1.0);
    ntcl_engine.Contract(c_tensor, b_tensor, a_tensor, "C(i,j)=A(i,p)*B(p,j)",
                         -1.0, 1.0);
  }
}

// Implements:
// in each channel: C_12 = A_1p * B_p2 - B_1p * B_p2
void EvaluateScalar111CommutatorRefImpl(const Scalar1BOperator& a,
                                        const Scalar1BOperator& b,
                                        Scalar1BOperator& c) {
  // Underlying modelspace should be identical
  Expects(a.GetModelSpacePtr() == b.GetModelSpacePtr());
  Expects(a.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ms = a.GetModelSpace();

  for (std::size_t chan_index = 0; chan_index < ms.NumberOfChannels();
       chan_index += 1) {
    const auto& chan = ms.ChannelAtIndex(chan_index);
    const auto dim_1 = chan.BraChannel().size();
    // 1, 2, and p channel are the same
    const auto dim_2 = dim_1;
    const auto dim_p = dim_1;

    auto& c_tensor = c.GetMutableTensorAtIndex(chan_index);
    const auto& a_tensor = a.GetTensorAtIndex(chan_index);
    const auto& b_tensor = b.GetTensorAtIndex(chan_index);

    for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
      for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
        for (std::size_t p = 0; p < dim_p; p += 1) {
          c_tensor(i1, i2) += a_tensor(i1, p) * b_tensor(p, i2);
          c_tensor(i1, i2) -= b_tensor(i1, p) * a_tensor(p, i2);
        }
      }
    }
  }
}
}  // namespace imsrg
