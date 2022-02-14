// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_OPERATOR_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_OPERATOR_CHANNEL_H_

#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
// Class for the non-single-particle quantum numbers in a 2-body channel.
class Scalar2BOpChannel {
 public:
  explicit Scalar2BOpChannel(TotalAngMom jj, Parity p, IsospinProj m_tt);

  TotalAngMom JJ() const { return jj_; }
  Parity P() const { return p_; }
  IsospinProj M_TT() const { return m_tt_; }

  template <typename H>
  friend H AbslHashValue(H h, Scalar2BOpChannel& o) {
    return H::combine(std::move(h), o.jj_, o.p_, o.m_tt_);
  }

  void swap(Scalar2BOpChannel& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
    swap(p_, other.p_);
    swap(m_tt_, other.m_tt_);
  }

 private:
  imsrg::TotalAngMom jj_;
  imsrg::Parity p_;
  imsrg::IsospinProj m_tt_;
};

inline void swap(Scalar2BOpChannel& a, Scalar2BOpChannel& b) noexcept {
  a.swap(b);
}

bool operator==(const Scalar2BOpChannel& a, const Scalar2BOpChannel& b);
inline bool operator!=(const Scalar2BOpChannel& a, const Scalar2BOpChannel& b) {
  return !(a == b);
}
}  // namespace imsrg
#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_OPERATOR_CHANNEL_H_
