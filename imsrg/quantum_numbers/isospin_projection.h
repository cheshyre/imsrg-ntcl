// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_ISOSPIN_PROJECTION_H_
#define IMSRG_QUANTUM_NUMBERS_ISOSPIN_PROJECTION_H_

#include <utility>

#include "imsrg/quantum_numbers/coupling/m_jj.h"

namespace imsrg {

class IsospinProj {
 public:
  explicit IsospinProj(int m_tt) : m_tt_(m_tt) {}
  explicit IsospinProj(M_JJ m_tt) : IsospinProj(m_tt.AsInt()) {}

  static IsospinProj Proton() { return IsospinProj(1); }
  static IsospinProj Neutron() { return IsospinProj(-1); }

  int AsInt() const { return m_tt_; }
  M_JJ AsM_JJ() const { return M_JJ(m_tt_); }

  IsospinProj& operator+=(IsospinProj other) {
    m_tt_ += other.m_tt_;
    return *this;
  }
  IsospinProj& operator-=(IsospinProj other) {
    m_tt_ -= other.m_tt_;
    return *this;
  }

  void swap(IsospinProj& other) noexcept {
    using std::swap;
    swap(m_tt_, other.m_tt_);
  }

  template <typename H>
  friend H AbslHashValue(H h, const IsospinProj& o) {
    return H::combine(std::move(h), o.m_tt_);
  }

 private:
  int m_tt_;
};

inline void swap(IsospinProj& a, IsospinProj& b) noexcept { a.swap(b); }
inline bool operator<(IsospinProj a, IsospinProj b) {
  return a.AsInt() < b.AsInt();
}
inline bool operator==(IsospinProj a, IsospinProj b) {
  return a.AsInt() == b.AsInt();
}
inline bool operator<=(IsospinProj a, IsospinProj b) {
  return a.AsInt() <= b.AsInt();
}
inline bool operator>(IsospinProj a, IsospinProj b) {
  return a.AsInt() > b.AsInt();
}
inline bool operator!=(IsospinProj a, IsospinProj b) {
  return a.AsInt() != b.AsInt();
}
inline bool operator>=(IsospinProj a, IsospinProj b) {
  return a.AsInt() >= b.AsInt();
}

inline IsospinProj operator+(IsospinProj a, IsospinProj b) {
  IsospinProj c(a);
  c += b;
  return c;
}

inline IsospinProj operator-(IsospinProj a, IsospinProj b) {
  IsospinProj c(a);
  c -= b;
  return c;
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_ISOSPIN_PROJECTION_H_
