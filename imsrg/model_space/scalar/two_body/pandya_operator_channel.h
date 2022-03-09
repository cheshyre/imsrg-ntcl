// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_OPERATOR_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_OPERATOR_CHANNEL_H_

#include <cstdint>
#include <utility>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class Scalar2BPanydaOpChannel {
 public:
  explicit Scalar2BPanydaOpChannel(TotalAngMom jj, Parity p,
                                   IsospinProj m_ttau);

  // Default copy, move, dtor

  imsrg::TotalAngMom JJ() const;
  imsrg::Parity P() const;
  imsrg::IsospinProj M_TTau() const;

  template <typename H>
  friend H AbslHashValue(H h, const Scalar2BPanydaOpChannel& o) {
    return H::combine(std::move(h), o.packed_rep_);
  }

  friend bool operator==(const Scalar2BPanydaOpChannel& a,
                         const Scalar2BPanydaOpChannel& b) {
    return a.packed_rep_ == b.packed_rep_;
  }

  friend bool operator!=(const Scalar2BPanydaOpChannel& a,
                         const Scalar2BPanydaOpChannel& b) {
    return a.packed_rep_ != b.packed_rep_;
  }

  void swap(Scalar2BPanydaOpChannel& other) noexcept {
    using std::swap;
    swap(packed_rep_, other.packed_rep_);
  }

 private:
  std::uint16_t packed_rep_;
};

inline void swap(Scalar2BPanydaOpChannel& a,
                 Scalar2BPanydaOpChannel& b) noexcept {
  a.swap(b);
}

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_OPERATOR_CHANNEL_H_
