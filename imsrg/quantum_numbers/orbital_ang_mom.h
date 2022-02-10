// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_ORBITAL_ANG_MOM_H_
#define IMSRG_QUANTUM_NUMBERS_ORBITAL_ANG_MOM_H_

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/parity.h"

namespace imsrg {
class OrbitalAngMom {
 public:
  explicit OrbitalAngMom(int l) : l_(l) { Expects(l >= 0); }
  explicit OrbitalAngMom(JJ ll) : OrbitalAngMom(ll.AsInt() / 2) {
    Expects(ll >= JJ(0));
    Expects(ll.AsInt() % 2 == 0);
  }

  // Default copy, move, and destructor

  int AsInt() const { return l_; }
  JJ AsJJ() const { return JJ(2 * l_); }
  imsrg::Parity Parity() const {
    if (l_ % 2 == 0) {
      return Parity::Even();
    }
    return Parity::Odd();
  }

  void swap(OrbitalAngMom& other) noexcept {
    using std::swap;
    swap(l_, other.l_);
  }

 private:
  int l_;
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
