// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_222_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_222_H_

#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {
// Evaluates scalar [2, 2] -> 2 commutator.
void EvaluateScalar222Commutator(const Scalar2BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar2BOperator& c);

// Evaluates scalar [2, 2] -> 2 commutator.
void EvaluateScalar222CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar2BOperator& c);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_222_H_
