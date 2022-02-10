// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_SPIN_H_
#define IMSRG_QUANTUM_NUMBERS_SPIN_H_

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {
class Spin {
 public:
  explicit Spin(int jj) : jj_(jj) { Expects(jj >= 0); }
  explicit Spin(JJ jj) : Spin(jj.AsInt()) { Expects(jj >= JJ(0)); }

  static Spin OneHalf() { return Spin(1); }

  // Default copy, move, and destructor

  int AsInt() const { return jj_; }
  JJ AsJJ() const { return JJ(jj_); }

  void swap(Spin& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }

 private:
  int jj_;
};

inline void swap(Spin& a, Spin& b) noexcept { a.swap(b); }
inline bool operator<(Spin a, Spin b) { return a.AsInt() < b.AsInt(); }
inline bool operator==(Spin a, Spin b) { return a.AsInt() == b.AsInt(); }
inline bool operator<=(Spin a, Spin b) { return a.AsInt() <= b.AsInt(); }
inline bool operator>(Spin a, Spin b) { return a.AsInt() > b.AsInt(); }
inline bool operator!=(Spin a, Spin b) { return a.AsInt() != b.AsInt(); }
inline bool operator>=(Spin a, Spin b) { return a.AsInt() >= b.AsInt(); }

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_SPIN_H_
