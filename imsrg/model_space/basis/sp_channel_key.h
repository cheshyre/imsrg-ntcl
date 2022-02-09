// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_

#include <cmath>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
inline std::size_t ComputeSPChannelKeyIndex(TotalAngMom jj, Parity p,
                                            IsospinProj m_tt) {
  // m_t should be -1/2 or 1/2 (nucleon)
  Expects(std::abs(m_tt.AsInt()) == 1);

  std::size_t index = 0;
  if (m_tt == IsospinProj::Neutron()) {
    index = 0;
  } else {  // Proton
    index = 1;
  }

  if (p.IsEven()) {
    index += 0;
  } else {  // Odd
    index += 2;
  }

  index += 4 * static_cast<std::size_t>(jj.AsInt());

  return index;
}
}  // namespace detail

class SPChannelKey {
 private:
  TotalAngMom jj_;
  Parity p_;
  IsospinProj m_tt_;
  std::size_t index_;

 public:
  explicit SPChannelKey(TotalAngMom jj, Parity p, IsospinProj m_tt)
      : jj_(jj),
        p_(p),
        m_tt_(m_tt),
        index_(imsrg::detail::ComputeSPChannelKeyIndex(jj, p, m_tt)) {
    // j should be half integer
    Expects(jj_.AsInt() % 2 != 0);
    // m_t should be -1/2 or 1/2 (nucleon)
    Expects(std::abs(m_tt_.AsInt()) == 1);
  }

  explicit SPChannelKey(JJ_P_M_TT jjpmtt)
      : SPChannelKey(jjpmtt.JJ(), jjpmtt.P(), jjpmtt.M_TT()) {}

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
};

inline void swap(SPChannelKey& a, SPChannelKey& b) noexcept { a.swap(b); }

inline bool operator==(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() == b.Index();
}

inline bool operator!=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() != b.Index();
}

inline bool operator<(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() < b.Index();
}

inline bool operator<=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() <= b.Index();
}

inline bool operator>(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() > b.Index();
}

inline bool operator>=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() >= b.Index();
}

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_KEY_H_
