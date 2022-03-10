// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPERATOR_SCALAR_TWO_BODY_ANTISYMMETRY_H_
#define IMSRG_OPERATOR_SCALAR_TWO_BODY_ANTISYMMETRY_H_

#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {

void AntisymmetrizeOperatorInChannel(Scalar2BOperator& op,
                                     Scalar2BChannelKey chankey);
}

#endif  // IMSRG_OPERATOR_SCALAR_TWO_BODY_ANTISYMMETRY_H_
