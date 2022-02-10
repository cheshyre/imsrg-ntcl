// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/states.h"

#include <utility>

#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/occupation_number.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
SPState::SPState(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                 imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt,
                 imsrg::OccupationNumber occ)
    : n_(n), l_(l), jj_(jj), m_tt_(m_tt), occ_(occ) {
  // Possible check for |2 * l - jj| == 1
}

SPState::SPState(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                 imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt)
    : SPState(n, l, jj, m_tt, imsrg::OccupationNumber::Particle()) {}

imsrg::HOEnergy SPState::E() const { return imsrg::HOEnergy(n_, l_); }

imsrg::JJ_P_M_TT SPState::GetJJ_P_M_TT() const {
  return imsrg::JJ_P_M_TT(jj_, l_.Parity(), m_tt_);
}

bool operator==(const SPState& a, const SPState& b) {
  return (a.RadialN() == b.RadialN()) && (a.L() == b.L()) &&
         (a.JJ() == b.JJ()) && (a.M_TT() == b.M_TT()) &&
         (a.OccupationN() == b.OccupationN());
}

}  // namespace imsrg
