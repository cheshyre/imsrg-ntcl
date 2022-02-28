// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_ISOSPIN_H_
#define IMSRG_QUANTUM_NUMBERS_ISOSPIN_H_

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/phases.h"

namespace imsrg {
class Isospin {
 public:
  explicit Isospin(int tt) : tt_(tt) { Expects(tt >= 0); }
  explicit Isospin(JJ tt) : Isospin(tt.AsInt()) {}

  static Isospin Nucleon() { return Isospin(1); }

  // Default copy, move, and destructor

  int AsInt() const { return tt_; }
  JJ AsJJ() const { return JJ(tt_); }
  JJPhase Phase(int prefactor = 1) const { return AsJJ().Phase(prefactor); }

  bool IsHalfInteger() const { return tt_ % 2 == 1; }
  bool IsInteger() const { return tt_ % 2 == 0; }

  void swap(Isospin& other) noexcept {
    using std::swap;
    swap(tt_, other.tt_);
  }

 private:
  std::int8_t tt_;
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
