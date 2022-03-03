// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_RADIAL_EXCITATION_NUMBER_H_
#define IMSRG_QUANTUM_NUMBERS_RADIAL_EXCITATION_NUMBER_H_

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"

namespace imsrg {
class RadialExcitationNumber {
 public:
  explicit RadialExcitationNumber(int n) : n_(n) { Expects(n >= 0); }

  // Default copy, move, and destructor

  int AsInt() const { return n_; }

  template <typename H>
  friend H AbslHashValue(H h, const RadialExcitationNumber& o) {
    return H::combine(std::move(h), o.n_);
  }

  void swap(RadialExcitationNumber& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
  }

 private:
  std::int8_t n_;
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
