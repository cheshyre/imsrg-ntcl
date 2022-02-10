// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/jj_p_m_tt.h"

#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
JJ_P_M_TT::JJ_P_M_TT(TotalAngMom jj, Parity p, IsospinProj m_tt)
    : jj_(jj), p_(p), m_tt_(m_tt) {}

void JJ_P_M_TT::swap(JJ_P_M_TT& other) noexcept {
  using std::swap;
  swap(jj_, other.jj_);
  swap(p_, other.p_);
  swap(m_tt_, other.m_tt_);
}

bool operator==(const JJ_P_M_TT& a, const JJ_P_M_TT& b) {
  return (a.JJ() == b.JJ()) && (a.P() == b.P()) && (a.M_TT() == b.M_TT());
}
bool operator!=(const JJ_P_M_TT& a, const JJ_P_M_TT& b) { return !(a == b); }

}  // namespace imsrg
