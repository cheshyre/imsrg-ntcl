// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_220_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_220_H_

#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {
// Evaluates scalar [2, 2] -> 0 commutator.
double EvaluateScalar220Commutator(const Scalar2BOperator& a,
                                   const Scalar2BOperator& b);

// Evaluates scalar [2, 2] -> 0 commutator.
double EvaluateScalar220CommutatorRefImpl(const Scalar2BOperator& a,
                                          const Scalar2BOperator& b);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_220_H_
