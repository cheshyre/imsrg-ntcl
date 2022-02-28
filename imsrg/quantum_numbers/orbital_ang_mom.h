// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_ORBITAL_ANG_MOM_H_
#define IMSRG_QUANTUM_NUMBERS_ORBITAL_ANG_MOM_H_

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/phases.h"
#include "imsrg/quantum_numbers/parity.h"

namespace imsrg {
class OrbitalAngMom {
 public:
  explicit OrbitalAngMom(int l) : l_(l) { Expects(l >= 0); }
  explicit OrbitalAngMom(JJ ll) : OrbitalAngMom(ll.AsInt() / 2) {
    Expects(ll.IsInteger());
  }

  // Default copy, move, and destructor

  int AsInt() const { return l_; }
  JJ AsJJ() const { return JJ(2 * l_); }
  JJPhase Phase(int prefactor = 1) const { return AsJJ().Phase(prefactor); }
  imsrg::Parity Parity() const {
    if (l_ % 2 == 0) {
      return Parity::Even();
    }
    return Parity::Odd();
  }

  template <typename H>
  friend H AbslHashValue(H h, const OrbitalAngMom& o) {
    return H::combine(std::move(h), o.l_);
  }

  void swap(OrbitalAngMom& other) noexcept {
    using std::swap;
    swap(l_, other.l_);
  }

 private:
  std::int8_t l_;
};

inline void swap(OrbitalAngMom& a, OrbitalAngMom& b) noexcept { a.swap(b); }
inline bool operator<(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() < b.AsInt();
}
inline bool operator==(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() == b.AsInt();
}
inline bool operator<=(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() <= b.AsInt();
}
inline bool operator>(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() > b.AsInt();
}
inline bool operator!=(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() != b.AsInt();
}
inline bool operator>=(OrbitalAngMom a, OrbitalAngMom b) {
  return a.AsInt() >= b.AsInt();
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_ORBITAL_ANG_MOM_H_
