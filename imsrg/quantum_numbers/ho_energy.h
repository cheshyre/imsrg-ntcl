// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_HO_ENERGY_H_
#define IMSRG_QUANTUM_NUMBERS_HO_ENERGY_H_

#include <utility>
#include <vector>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"

namespace imsrg {
// Structured return type for packaged N, L returns.
// This should not be used for any meaningful persistent objects.
struct N_L {
  RadialExcitationNumber n;
  OrbitalAngMom l;
};

class HOEnergy {
 private:
  int e_;

 public:
  explicit HOEnergy(int e) : e_(e) { Expects(e >= 0); }
  explicit HOEnergy(OrbitalAngMom l, RadialExcitationNumber n)
      : HOEnergy(2 * n.AsInt() + l.AsInt()) {}
  explicit HOEnergy(RadialExcitationNumber n, OrbitalAngMom l)
      : HOEnergy(2 * n.AsInt() + l.AsInt()) {}

  // Default copy, move, and destructor

  int AsInt() const { return e_; }

  std::vector<N_L> GenerateSubShellQuantumNumbers() const {
    std::vector<N_L> shells;
    shells.reserve(e_ / 2 + 1);
    for (int n = 0; n <= e_ / 2; n++) {
      int l = e_ - 2 * n;
      shells.push_back({RadialExcitationNumber(n), OrbitalAngMom(l)});
    }
    return shells;
  }

  void swap(HOEnergy& other) noexcept {
    using std::swap;
    swap(e_, other.e_);
  }
};

inline void swap(HOEnergy& a, HOEnergy& b) noexcept { a.swap(b); }
inline bool operator<(HOEnergy a, HOEnergy b) { return a.AsInt() < b.AsInt(); }
inline bool operator==(HOEnergy a, HOEnergy b) {
  return a.AsInt() == b.AsInt();
}
inline bool operator<=(HOEnergy a, HOEnergy b) {
  return a.AsInt() <= b.AsInt();
}
inline bool operator>(HOEnergy a, HOEnergy b) { return a.AsInt() > b.AsInt(); }
inline bool operator!=(HOEnergy a, HOEnergy b) {
  return a.AsInt() != b.AsInt();
}
inline bool operator>=(HOEnergy a, HOEnergy b) {
  return a.AsInt() >= b.AsInt();
}

inline std::vector<HOEnergy> GenerateHOEnergyShells(HOEnergy emax) {
  std::vector<HOEnergy> shells;
  shells.reserve(emax.AsInt() + 1);

  for (int e = 0; HOEnergy(e) <= emax; e++) {
    shells.push_back(HOEnergy(e));
  }

  return shells;
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_HO_ENERGY_H_
