// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_JJ_P_M_TT_H_
#define IMSRG_MODEL_SPACE_JJ_P_M_TT_H_

#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class JJ_P_M_TT {
 public:
  explicit JJ_P_M_TT(TotalAngMom jj, Parity p, IsospinProj m_tt);

  // Default copy, move, and destructor

  TotalAngMom JJ() const { return jj_; }
  Parity P() const { return p_; }
  IsospinProj M_TT() const { return m_tt_; }

  void swap(JJ_P_M_TT& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
    swap(p_, other.p_);
    swap(m_tt_, other.m_tt_);
  }

  template <typename H>
  friend H AbslHashValue(H h, const JJ_P_M_TT& jjpmtt) {
    return H::combine(std::move(h), jjpmtt.jj_, jjpmtt.p_, jjpmtt.m_tt_);
  }

 private:
  TotalAngMom jj_;
  Parity p_;
  IsospinProj m_tt_;
};

inline void swap(JJ_P_M_TT& a, JJ_P_M_TT& b) noexcept { a.swap(b); }

bool operator==(const JJ_P_M_TT& a, const JJ_P_M_TT& b);
bool operator!=(const JJ_P_M_TT& a, const JJ_P_M_TT& b);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_JJ_P_M_TT_H_
