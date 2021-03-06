// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_TOTAL_ANG_MOM_H_
#define IMSRG_QUANTUM_NUMBERS_TOTAL_ANG_MOM_H_

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/phases.h"

namespace imsrg {
class TotalAngMom {
 public:
  explicit TotalAngMom(int jj) : jj_(jj) { Expects(jj >= 0); }
  explicit TotalAngMom(JJ jj) : TotalAngMom(jj.AsInt()) {}

  // Default copy, move, and destructor

  int AsInt() const { return jj_; }
  JJ AsJJ() const { return JJ(jj_); }
  JJPhase Phase(int prefactor = 1) const { return AsJJ().Phase(prefactor); }

  bool IsHalfInteger() const { return jj_ % 2 == 1; }
  bool IsInteger() const { return jj_ % 2 == 0; }

  void swap(TotalAngMom& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }

  template <typename H>
  friend H AbslHashValue(H h, const TotalAngMom& o) {
    return H::combine(std::move(h), o.jj_);
  }

 private:
  std::int8_t jj_;
};

inline void swap(TotalAngMom& a, TotalAngMom& b) noexcept { a.swap(b); }
inline bool operator<(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() < b.AsInt();
}
inline bool operator==(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() == b.AsInt();
}
inline bool operator<=(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() <= b.AsInt();
}
inline bool operator>(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() > b.AsInt();
}
inline bool operator!=(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() != b.AsInt();
}
inline bool operator>=(TotalAngMom a, TotalAngMom b) {
  return a.AsInt() >= b.AsInt();
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_TOTAL_ANG_MOM_H_
