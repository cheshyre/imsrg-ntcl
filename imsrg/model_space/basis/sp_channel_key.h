// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_

#include <utility>

#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

class SPChannelKey {
 public:
  explicit SPChannelKey(TotalAngMom jj, Parity p, IsospinProj m_tt);

  explicit SPChannelKey(JJ_P_M_TT jjpmtt);

  // Default copy, move, and destructor

  TotalAngMom JJ() const { return jj_; }
  Parity P() const { return p_; }
  IsospinProj M_TT() const { return m_tt_; }

  // Unique index, computed from jj, p, m_tt
  std::size_t Index() const { return index_; }

  void swap(SPChannelKey& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
    swap(p_, other.p_);
    swap(m_tt_, other.m_tt_);
    swap(index_, other.index_);
  }

  // Hash value, independent of secured basis ptr
  template <typename H>
  friend H AbslHashValue(H h, const SPChannelKey& o) {
    return H::combine(std::move(h), o.jj_, o.p_, o.m_tt_);
  }

 private:
  TotalAngMom jj_;
  Parity p_;
  IsospinProj m_tt_;
  std::size_t index_;
};

inline void swap(SPChannelKey& a, SPChannelKey& b) noexcept { a.swap(b); }

bool operator==(const SPChannelKey& a, const SPChannelKey& b);
bool operator!=(const SPChannelKey& a, const SPChannelKey& b);
bool operator<(const SPChannelKey& a, const SPChannelKey& b);
bool operator<=(const SPChannelKey& a, const SPChannelKey& b);
bool operator>(const SPChannelKey& a, const SPChannelKey& b);
bool operator>=(const SPChannelKey& a, const SPChannelKey& b);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_
