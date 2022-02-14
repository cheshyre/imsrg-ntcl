// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/operator_channel.h"

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
Scalar2BOpChannel::Scalar2BOpChannel(TotalAngMom jj, Parity p, IsospinProj m_tt)
    : jj_(jj), p_(p), m_tt_(m_tt) {
  Expects(jj_.IsInteger());
  Expects(m_tt_.IsInteger());
}

bool operator==(const Scalar2BOpChannel& a, const Scalar2BOpChannel& b) {
  return ((a.JJ() == b.JJ()) && (a.P() == b.P()) && (a.M_TT() == b.M_TT()));
}
}  // namespace imsrg
