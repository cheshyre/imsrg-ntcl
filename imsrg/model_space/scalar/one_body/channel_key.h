// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_KEY_H_

#include <utility>

#include "imsrg/model_space/scalar/one_body/operator_channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"

namespace imsrg {
class Scalar1BChannelKey {
 public:
  explicit Scalar1BChannelKey(SPChannelKey chan_key_bra,
                              SPChannelKey chan_key_ket);

  SPChannelKey BraChannelKey() const { return bra_chan_key_; }
  SPChannelKey KetChannelKey() const { return ket_chan_key_; }
  Scalar1BOpChannel OpChannel() const { return op_chan_; }

  template <typename H>
  friend H AbslHashValue(H h, const Scalar1BChannelKey& o) {
    return H::combine(std::move(h), o.bra_chan_key_, o.ket_chan_key_,
                      o.op_chan_);
  }

  void swap(Scalar1BChannelKey& other) noexcept {
    using std::swap;
    swap(bra_chan_key_, other.bra_chan_key_);
    swap(ket_chan_key_, other.ket_chan_key_);
    swap(op_chan_, other.op_chan_);
  }

 private:
  SPChannelKey bra_chan_key_;
  SPChannelKey ket_chan_key_;
  Scalar1BOpChannel op_chan_;

  static Scalar1BOpChannel GenerateOpChannel(const SPChannelKey& bra_chan_key,
                                             const SPChannelKey& ket_chan_key);
};

inline void swap(Scalar1BChannelKey& a, Scalar1BChannelKey& b) noexcept {
  a.swap(b);
}

bool operator==(const Scalar1BChannelKey& a, const Scalar1BChannelKey& b);
inline bool operator!=(const Scalar1BChannelKey& a,
                       const Scalar1BChannelKey& b) {
  return !(a == b);
}
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_KEY_H_
