// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_STATES_H_
#define IMSRG_MODEL_SPACE_BASIS_STATES_H_

#include <utility>

#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/occupation_number.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class SPState {
 private:
  imsrg::RadialExcitationNumber n_;
  imsrg::OrbitalAngMom l_;
  imsrg::TotalAngMom jj_;
  imsrg::IsospinProj m_tt_;
  imsrg::OccupationNumber occ_;

 public:
  // Construct single-particle state
  explicit SPState(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                   imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt,
                   imsrg::OccupationNumber occ)
      : n_(n), l_(l), jj_(jj), m_tt_(m_tt), occ_(occ) {
    // Possible check for |2 * l - jj| == 1
  }

  // Construct particle (occ=0) state (at least initially)
  explicit SPState(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                   imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt)
      : SPState(n, l, jj, m_tt, imsrg::OccupationNumber::Particle()) {}

  // Default copy, move, and destructor

  imsrg::RadialExcitationNumber RadialN() const { return n_; }

  imsrg::OrbitalAngMom L() const { return l_; }

  imsrg::TotalAngMom JJ() const { return jj_; }

  imsrg::IsospinProj M_TT() const { return m_tt_; }

  imsrg::OccupationNumber OccupationN() const { return occ_; }

  imsrg::HOEnergy E() const { return imsrg::HOEnergy(n_, l_); }

  void SetOccupationN(imsrg::OccupationNumber occ) { occ_ = occ; }

  imsrg::JJ_P_M_TT GetJJ_P_M_TT() const {
    return imsrg::JJ_P_M_TT(jj_, l_.Parity(), m_tt_);
  }

  void swap(SPState& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
    swap(l_, other.l_);
    swap(jj_, other.jj_);
    swap(m_tt_, other.m_tt_);
    swap(occ_, other.occ_);
  }
};

inline void swap(SPState& a, SPState& b) noexcept { a.swap(b); }

inline bool operator==(const SPState& a, const SPState& b) {
  return (a.RadialN() == b.RadialN()) && (a.L() == b.L()) &&
         (a.JJ() == b.JJ()) && (a.M_TT() == b.M_TT()) &&
         (a.OccupationN() == b.OccupationN());
}

inline bool operator!=(const SPState& a, const SPState& b) { return !(a == b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_BASIS_STATES_H_
