// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_M_JJ_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_M_JJ_H_

#include <cmath>
#include <utility>

#include "imsrg/quantum_numbers/coupling/phases.h"

namespace imsrg {
class M_JJ {
 public:
  /**
   * @brief Construct new M_JJ (2 * m_j, where m_j is angular momentum
   * projection) from integer.
   *
   * @param m_jj
   */
  explicit M_JJ(int m_jj) : m_jj_(m_jj) {}

  // Default copy, move, and destructor

  int AsInt() const { return m_jj_; }
  bool IsHalfInteger() const { return std::abs(m_jj_) % 2 == 1; }
  bool IsInteger() const { return std::abs(m_jj_) % 2 == 0; }
  JJPhase Phase(int prefactor = 1) const { return JJPhase(m_jj_, prefactor); }

  M_JJ& operator+=(M_JJ other) {
    m_jj_ += other.m_jj_;
    return *this;
  }
  M_JJ& operator-=(M_JJ other) {
    m_jj_ -= other.m_jj_;
    return *this;
  }

  void swap(M_JJ& other) noexcept {
    using std::swap;
    swap(m_jj_, other.m_jj_);
  }

 private:
  int m_jj_;
};

inline void swap(M_JJ& a, M_JJ& b) noexcept { a.swap(b); }
inline bool operator<(M_JJ a, M_JJ b) { return a.AsInt() < b.AsInt(); }
inline bool operator==(M_JJ a, M_JJ b) { return a.AsInt() == b.AsInt(); }
inline bool operator<=(M_JJ a, M_JJ b) { return a.AsInt() <= b.AsInt(); }
inline bool operator>(M_JJ a, M_JJ b) { return a.AsInt() > b.AsInt(); }
inline bool operator!=(M_JJ a, M_JJ b) { return a.AsInt() != b.AsInt(); }
inline bool operator>=(M_JJ a, M_JJ b) { return a.AsInt() >= b.AsInt(); }

inline M_JJ operator+(M_JJ a, M_JJ b) {
  M_JJ c(a);
  c += b;
  return c;
}

inline M_JJ operator-(M_JJ a, M_JJ b) {
  M_JJ c(a);
  c -= b;
  return c;
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_M_JJ_H_
