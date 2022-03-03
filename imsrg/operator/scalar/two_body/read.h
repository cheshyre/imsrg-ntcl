// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPERATOR_SCALAR_TWO_BODY_READ_H_
#define IMSRG_OPERATOR_SCALAR_TWO_BODY_READ_H_

#include "imsrg/files/formats/me2jp.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {

void ReadOperatorFromME2JP(const ME2JPFile& me2jp, Scalar2BOperator& op);
}

#endif  // IMSRG_OPERATOR_SCALAR_TWO_BODY_READ_H_
