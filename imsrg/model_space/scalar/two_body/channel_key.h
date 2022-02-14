// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_KEY_H_

#include <utility>

#include "imsrg/model_space/scalar/two_body/operator_channel.h"
#include "imsrg/model_space/scalar/two_body/state_channel_key.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class Scalar2BChannelKey {
 public:
  explicit Scalar2BChannelKey(Scalar2BStateChannelKey bra_chan_key,
                              Scalar2BStateChannelKey ket_chan_key,
                              TotalAngMom jj_2b);

  Scalar2BStateChannelKey BraChannelKey() const { return bra_chan_key_; }
  Scalar2BStateChannelKey KetChannelKey() const { return ket_chan_key_; }
  Scalar2BOpChannel OpChannel() const { return op_chan_; }

  template <typename H>
  friend H AbslHashValue(H h, const Scalar2BChannelKey& o) {
    return H::combine(std::move(h), o.bra_chan_key_, o.ket_chan_key_,
                      o.op_chan_);
  }

  void swap(Scalar2BChannelKey& other) noexcept {
    using std::swap;
    swap(bra_chan_key_, other.bra_chan_key_);
    swap(ket_chan_key_, other.ket_chan_key_);
    swap(op_chan_, other.op_chan_);
  }

 private:
  Scalar2BStateChannelKey bra_chan_key_;
  Scalar2BStateChannelKey ket_chan_key_;
  Scalar2BOpChannel op_chan_;

  static Scalar2BOpChannel GenerateOpChannel(
      const Scalar2BStateChannelKey& bra_chan_key,
      const Scalar2BStateChannelKey& ket_chan_key, TotalAngMom jj_2b);
};

inline void swap(Scalar2BChannelKey& a, Scalar2BChannelKey& b) noexcept {
  a.swap(b);
}

bool operator==(const Scalar2BChannelKey& a, const Scalar2BChannelKey& b);
inline bool operator!=(const Scalar2BChannelKey& a,
                       const Scalar2BChannelKey& b) {
  return !(a == b);
}
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_KEY_H_
