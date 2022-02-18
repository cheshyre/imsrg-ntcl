// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_STRING_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_STRING_H_

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class SPStateString {
 public:
  static std::string BasicString(RadialExcitationNumber n, OrbitalAngMom l,
                                 TotalAngMom jj, IsospinProj m_tt);

  static std::vector<std::string> OrbitalAngMomLookup();
  static std::vector<std::string> CanonicallyOrderedOrbitals();
  static std::vector<std::string> CanonicallyOrderedProtonOrbitals();
  static std::vector<std::string> CanonicallyOrderedNeutronOrbitals();
  static std::vector<SPStateString> GetProtonOrbitalsUpToMax(
      const SPStateString& max_state);
  static std::vector<SPStateString> GetNeutronOrbitalsUpToMax(
      const SPStateString& max_state);

  explicit SPStateString(RadialExcitationNumber n, OrbitalAngMom l,
                         TotalAngMom jj, IsospinProj m_tt);
  explicit SPStateString(std::string_view state_string);

  // Default copy, move, and dtor

  std::string String() const { return str_; }
  RadialExcitationNumber RadialN() const { return n_; }
  OrbitalAngMom L() const { return l_; }
  TotalAngMom JJ() const { return jj_; }
  IsospinProj M_TT() const { return m_tt_; }

  void swap(SPStateString& other) noexcept {
    using std::swap;
    swap(str_, other.str_);
    swap(n_, other.n_);
    swap(l_, other.l_);
    swap(jj_, other.jj_);
    swap(m_tt_, other.m_tt_);
  }

 private:
  std::string str_;
  RadialExcitationNumber n_;
  OrbitalAngMom l_;
  TotalAngMom jj_;
  IsospinProj m_tt_;
};
inline void swap(SPStateString& a, SPStateString& b) noexcept { a.swap(b); }
bool operator==(const SPStateString& a, const SPStateString& b);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_STRING_H_
