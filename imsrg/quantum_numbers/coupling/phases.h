// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_PHASES_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_PHASES_H_

#include <utility>

#include "imsrg/assert.h"

namespace imsrg {

namespace detail {
inline int Modulus(int x, int mod) {
  Expects(mod > 0);
  int val = x % mod;
  if (val < 0) {
    val += mod;
  }
  return val;
}

}  // namespace detail

class JJPhase {
 public:
  static JJPhase One() { return JJPhase(0); }
  static JJPhase MinusOne() { return JJPhase(2); }

  explicit JJPhase(int jj, int prefactor = 1) : jj_(prefactor * jj) {
    Expects((prefactor == 1) || (prefactor == -1));
  }

  // Default copy, move, and dtor

  bool IsValidAsInt() const { return imsrg::detail::Modulus(jj_, 2) == 0; }

  int AsInt() const {
    Expects(imsrg::detail::Modulus(jj_, 2) == 0);
    if (imsrg::detail::Modulus(jj_, 4) == 0) {
      return 1;
    }
    return -1;
  }

  JJPhase& operator*=(JJPhase other) {
    jj_ += other.jj_;
    return *this;
  }

  void swap(JJPhase& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }

 private:
  int jj_;
};

inline void swap(JJPhase& a, JJPhase& b) noexcept { a.swap(b); }

inline JJPhase operator*(JJPhase a, JJPhase b) {
  JJPhase c(a);
  c *= b;
  return c;
}

template <typename T>
inline JJPhase Phase(T a, int prefactor = 1) {
  return JJPhase(a.Phase(prefactor));
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_PHASES_H_
