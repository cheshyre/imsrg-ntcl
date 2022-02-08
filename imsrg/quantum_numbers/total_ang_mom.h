// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_TOTAL_ANG_MOM_H_
#define IMSRG_QUANTUM_NUMBERS_TOTAL_ANG_MOM_H_

#include <utility>

#include "gsl/assert"

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {
class TotalAngMom {
 private:
  int jj_;

 public:
  explicit TotalAngMom(int jj) : jj_(jj) { Expects(jj >= 0); }
  explicit TotalAngMom(JJ jj) : TotalAngMom(jj.AsInt()) {
    Expects(jj >= JJ(0));
  }

  // Default copy, move, and destructor

  int AsInt() const { return jj_; }
  JJ AsJJ() const { return JJ(jj_); }

  void swap(TotalAngMom& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }

  template <typename H>
  friend H AbslHashValue(H h, const TotalAngMom& o) {
    return H::combine(std::move(h), o.jj_);
  }
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
