// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_KEY_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_KEY_H_

#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class SPStateKey {
 public:
  // Construct single-particle state key
  explicit SPStateKey(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                      imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt);

  // Default copy, move, and destructor

  imsrg::RadialExcitationNumber RadialN() const { return n_; }

  imsrg::OrbitalAngMom L() const { return l_; }

  imsrg::TotalAngMom JJ() const { return jj_; }

  imsrg::IsospinProj M_TT() const { return m_tt_; }

  template <typename H>
  friend H AbslHashValue(H h, const SPStateKey& o) {
    return H::combine(std::move(h), o.n_, o.l_, o.jj_, o.m_tt_);
  }

  void swap(SPStateKey& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
    swap(l_, other.l_);
    swap(jj_, other.jj_);
    swap(m_tt_, other.m_tt_);
  }

 private:
  imsrg::RadialExcitationNumber n_;
  imsrg::OrbitalAngMom l_;
  imsrg::TotalAngMom jj_;
  imsrg::IsospinProj m_tt_;
};

inline void swap(SPStateKey& a, SPStateKey& b) noexcept { a.swap(b); }

bool operator==(const SPStateKey& a, const SPStateKey& b);

inline bool operator!=(const SPStateKey& a, const SPStateKey& b) {
  return !(a == b);
}
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_STATE_KEY_H_
