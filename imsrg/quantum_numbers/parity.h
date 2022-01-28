// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_PARITY_H_
#define IMSRG_QUANTUM_NUMBERS_PARITY_H_

#include <utility>

namespace imsrg {
class Parity {
 private:
  bool p_;
  explicit Parity(bool p) : p_(p) {}

 public:
  // Static factory functions for even and odd parity
  static Parity Even() { return Parity(true); }
  static Parity Odd() { return Parity(false); }

  // Default copy, move, and destructor

  bool IsEven() const { return p_; }
  bool IsOdd() const { return !p_; }

  Parity& operator+=(Parity other) {
    p_ = (p_ == other.p_);
    return *this;
  }
  Parity& operator-=(Parity other) {
    p_ = (p_ == other.p_);
    return *this;
  }

  void swap(Parity& other) noexcept {
    using std::swap;
    swap(p_, other.p_);
  }
};

inline void swap(Parity& a, Parity& b) noexcept { a.swap(b); }
// This ordering defines even < odd (and even == even, odd == odd)
inline bool operator<(Parity a, Parity b) { return a.IsEven() && b.IsOdd(); }
inline bool operator==(Parity a, Parity b) { return a.IsEven() == b.IsEven(); }
inline bool operator<=(Parity a, Parity b) { return (a == b) || (a < b); }
inline bool operator>(Parity a, Parity b) { return !(a <= b); }
inline bool operator!=(Parity a, Parity b) { return !(a == b); }
inline bool operator>=(Parity a, Parity b) { return !(a < b); }

inline Parity operator+(Parity a, Parity b) {
  Parity c(a);
  c += b;
  return c;
}

inline Parity operator-(Parity a, Parity b) {
  Parity c(a);
  c -= b;
  return c;
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_PARITY_H_
