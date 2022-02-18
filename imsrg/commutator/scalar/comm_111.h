// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_111_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_111_H_

#include "imsrg/operator/scalar/one_body/operator.h"

namespace imsrg {

void EvaluateScalar111Commutator(const Scalar1BOperator& a,
                                 const Scalar1BOperator& b,
                                 Scalar1BOperator& c);

void EvaluateScalar111CommutatorRefImpl(const Scalar1BOperator& a,
                                        const Scalar1BOperator& b,
                                        Scalar1BOperator& c);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_111_H_
