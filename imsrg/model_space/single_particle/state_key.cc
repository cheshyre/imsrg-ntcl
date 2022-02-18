// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/state_key.h"

#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
// Construct single-particle state key
SPStateKey::SPStateKey(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                       imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt)
    : n_(n), l_(l), jj_(jj), m_tt_(m_tt) {}

// Default copy, move, and destructor

bool operator==(const SPStateKey& a, const SPStateKey& b) {
  return (a.JJ() == b.JJ()) && (a.L() == b.L()) && (a.M_TT() == b.M_TT()) &&
         (a.RadialN() == b.RadialN());
}

}  // namespace imsrg
