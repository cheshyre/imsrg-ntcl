// Copyright 2022 Matthias Heinz
#ifndef IMSRG_COMMUTATOR_SCALAR_COMM_110_H_
#define IMSRG_COMMUTATOR_SCALAR_COMM_110_H_

#include "imsrg/operator/scalar/one_body/operator.h"

namespace imsrg {

double EvaluateScalar110Commutator(const Scalar1BOperator& a,
                                   const Scalar1BOperator& b);

double EvaluateScalar110CommutatorRefImpl(const Scalar1BOperator& a,
                                          const Scalar1BOperator& b);
}  // namespace imsrg

#endif  // IMSRG_COMMUTATOR_SCALAR_COMM_110_H_
