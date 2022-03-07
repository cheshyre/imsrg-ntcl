// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_KEY_H_

#include <cstdint>
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

  TotalAngMom JJ() const;
  Parity P() const;
  IsospinProj M_TT() const;

  // Unique index, computed from jj, p, m_tt
  std::size_t Index() const { return packed_rep_; }

  void swap(SPChannelKey& other) noexcept {
    using std::swap;
    swap(packed_rep_, other.packed_rep_);
  }

  // Hash value, independent of secured basis ptr
  template <typename H>
  friend H AbslHashValue(H h, const SPChannelKey& o) {
    return H::combine(std::move(h), o.packed_rep_);
  }

 private:
  std::uint8_t packed_rep_;
};

inline void swap(SPChannelKey& a, SPChannelKey& b) noexcept { a.swap(b); }

bool operator==(const SPChannelKey& a, const SPChannelKey& b);
bool operator!=(const SPChannelKey& a, const SPChannelKey& b);
bool operator<(const SPChannelKey& a, const SPChannelKey& b);
bool operator<=(const SPChannelKey& a, const SPChannelKey& b);
bool operator>(const SPChannelKey& a, const SPChannelKey& b);
bool operator>=(const SPChannelKey& a, const SPChannelKey& b);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_KEY_H_
