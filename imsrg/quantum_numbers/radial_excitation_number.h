// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_RADIAL_EXCITATION_NUMBER_H_
#define IMSRG_QUANTUM_NUMBERS_RADIAL_EXCITATION_NUMBER_H_

#include <utility>

#include "gsl/assert"

namespace imsrg {
class RadialExcitationNumber {
 private:
  int n_;

 public:
  explicit RadialExcitationNumber(int n) : n_(n) { Expects(n >= 0); }

  // Default copy, move, and destructor

  int AsInt() const { return n_; }

  void swap(RadialExcitationNumber& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
  }
};

inline void swap(RadialExcitationNumber& a,
                 RadialExcitationNumber& b) noexcept {
  a.swap(b);
}
inline bool operator<(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() < b.AsInt();
}
inline bool operator==(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() == b.AsInt();
}
inline bool operator<=(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() <= b.AsInt();
}
inline bool operator>(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() > b.AsInt();
}
inline bool operator!=(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() != b.AsInt();
}
inline bool operator>=(RadialExcitationNumber a, RadialExcitationNumber b) {
  return a.AsInt() >= b.AsInt();
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_RADIAL_EXCITATION_NUMBER_H_
