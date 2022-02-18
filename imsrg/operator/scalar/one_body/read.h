// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPERATOR_SCALAR_ONE_BODY_READ_H_
#define IMSRG_OPERATOR_SCALAR_ONE_BODY_READ_H_

#include "imsrg/files/formats/me1j.h"
#include "imsrg/operator/scalar/one_body/operator.h"

namespace imsrg {

void ReadOperatorFromME1J(const ME1JFile& me1j, Scalar1BOperator& op);
}

#endif  // IMSRG_OPERATOR_SCALAR_ONE_BODY_READ_H_
