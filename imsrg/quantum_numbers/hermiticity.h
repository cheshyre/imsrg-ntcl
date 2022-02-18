// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_HERMITICITY_H_
#define IMSRG_QUANTUM_NUMBERS_HERMITICITY_H_

#include <utility>

namespace imsrg {
class Hermiticity {
 public:
  static Hermiticity Hermitian() { return Hermiticity(1); }
  static Hermiticity AntiHermitian() { return Hermiticity(-1); }
  static Hermiticity CommutatorHermiticity(Hermiticity a, Hermiticity b) {
    if (a.herm_ == b.herm_) {
      return Hermiticity::AntiHermitian();
    }
    return Hermiticity::Hermitian();
  }

  // Default copy, move, and dtor

  bool IsHermitian() const { return herm_ == 1; }
  bool IsAntiHermitian() const { return herm_ == -1; }

  int Factor() const { return herm_; }

  void swap(Hermiticity& other) noexcept {
    using std::swap;
    swap(herm_, other.herm_);
  }

 private:
  int herm_;

  explicit Hermiticity(int herm) : herm_(herm) {}
};
inline void swap(Hermiticity& a, Hermiticity& b) noexcept { a.swap(b); }
inline bool operator==(const Hermiticity& a, const Hermiticity& b) {
  return a.Factor() == b.Factor();
}
inline bool operator!=(const Hermiticity& a, const Hermiticity& b) {
  return a.Factor() != b.Factor();
}
}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_HERMITICITY_H_
