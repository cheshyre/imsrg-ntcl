// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_OCCUPATION_NUMBER_H_
#define IMSRG_QUANTUM_NUMBERS_OCCUPATION_NUMBER_H_

#include <cmath>
#include <utility>

#include "gsl/assert"

namespace imsrg {

class OccupationNumber {
 private:
  double n_;

 public:
  explicit OccupationNumber(double n) : n_(n) {
    Expects(n >= 0.0);
    Expects(n <= 1.0);
  }

  static OccupationNumber Hole() { return OccupationNumber(1.0); }
  static OccupationNumber Particle() { return OccupationNumber(0.0); }

  // Default copy, move, and destructor

  double AsDouble() const { return n_; }
  double NBarAsDouble() const { return 1.0 - n_; }
  bool IsHole() const { return n_ == 1.0; }
  bool IsParticle() const { return n_ == 0.0; }
  bool IsValence() const { return n_ > 0.0 && n_ < 1.0; }

  void swap(OccupationNumber& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
  }
};

inline void swap(OccupationNumber& a, OccupationNumber& b) noexcept {
  a.swap(b);
}
inline bool operator<(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() < b.AsDouble();
}
inline bool operator==(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() == b.AsDouble();
}
inline bool operator<=(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() <= b.AsDouble();
}
inline bool operator>(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() > b.AsDouble();
}
inline bool operator!=(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() != b.AsDouble();
}
inline bool operator>=(OccupationNumber a, OccupationNumber b) {
  return a.AsDouble() >= b.AsDouble();
}
}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_OCCUPATION_NUMBER_H_
