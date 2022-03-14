// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_221_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_221_H_

#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {
// Evaluates scalar [2, 2] -> 1 commutator.
void EvaluateScalar221Commutator(const Scalar2BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar1BOperator& c);

// Evaluates scalar [2, 2] -> 1 commutator.
void EvaluateScalar221CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar1BOperator& c);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_221_H_
