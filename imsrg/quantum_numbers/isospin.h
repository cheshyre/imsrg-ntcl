// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_ISOSPIN_H_
#define IMSRG_QUANTUM_NUMBERS_ISOSPIN_H_

#include <utility>

#include "lib/GSL/include/gsl/assert"

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {
class Isospin {
 private:
  int jj_;

 public:
  explicit Isospin(int jj) : jj_(jj) { Expects(jj >= 0); }
  explicit Isospin(JJ jj) : Isospin(jj.AsInt()) { Expects(jj >= JJ(0)); }

  static Isospin Nucleon() { return Isospin(1); }

  // Default copy, move, and destructor

  int AsInt() const { return jj_; }
  JJ AsJJ() const { return JJ(jj_); }

  void swap(Isospin& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }
};

inline void swap(Isospin& a, Isospin& b) noexcept { a.swap(b); }
inline bool operator<(Isospin a, Isospin b) { return a.AsInt() < b.AsInt(); }
inline bool operator==(Isospin a, Isospin b) { return a.AsInt() == b.AsInt(); }
inline bool operator<=(Isospin a, Isospin b) { return a.AsInt() <= b.AsInt(); }
inline bool operator>(Isospin a, Isospin b) { return a.AsInt() > b.AsInt(); }
inline bool operator!=(Isospin a, Isospin b) { return a.AsInt() != b.AsInt(); }
inline bool operator>=(Isospin a, Isospin b) { return a.AsInt() >= b.AsInt(); }

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_ISOSPIN_H_
