// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_SPIN_H_
#define IMSRG_QUANTUM_NUMBERS_SPIN_H_

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/phases.h"

namespace imsrg {
class Spin {
 public:
  explicit Spin(int ss) : ss_(ss) { Expects(ss >= 0); }
  explicit Spin(JJ ss) : Spin(ss.AsInt()) {}

  static Spin OneHalf() { return Spin(1); }

  // Default copy, move, and destructor

  int AsInt() const { return ss_; }
  JJ AsJJ() const { return JJ(ss_); }
  JJPhase Phase(int prefactor = 1) const { return AsJJ().Phase(prefactor); }

  bool IsHalfInteger() const { return ss_ % 2 == 1; }
  bool IsInteger() const { return ss_ % 2 == 0; }

  void swap(Spin& other) noexcept {
    using std::swap;
    swap(ss_, other.ss_);
  }

 private:
  std::int8_t ss_;
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
