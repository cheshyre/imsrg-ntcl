// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_122_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_122_H_

#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {
// Evaluates scalar [1, 2] -> 2 commutator.
void EvaluateScalar122Commutator(const Scalar1BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar2BOperator& c);

// Evaluates scalar [1, 2] -> 2 commutator.
void EvaluateScalar122CommutatorRefImpl(const Scalar1BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar2BOperator& c);

// Evaluates scalar [2, 1] -> 2 commutator.
void EvaluateScalar212Commutator(const Scalar2BOperator& a,
                                 const Scalar1BOperator& b,
                                 Scalar2BOperator& c);

// Evaluates scalar [2, 1] -> 2 commutator.
void EvaluateScalar212CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar1BOperator& b,
                                        Scalar2BOperator& c);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_122_H_
