// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/operator_channel.h"

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
Scalar1BOpChannel::Scalar1BOpChannel(TotalAngMom jj, Parity p, IsospinProj m_tt)
    : jj_(jj), p_(p), m_tt_(m_tt) {
  Expects(jj_.IsHalfInteger());
  Expects(m_tt_.IsHalfInteger());
}

bool operator==(const Scalar1BOpChannel& a, const Scalar1BOpChannel& b) {
  return ((a.JJ() == b.JJ()) && (a.P() == b.P()) && (a.M_TT() == b.M_TT()));
}
}  // namespace imsrg
