// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_H_

#include <utility>

#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/model_space/single_particle/channel.h"

namespace imsrg {

class Scalar1BChannel {
 public:
  explicit Scalar1BChannel(const SPChannel& bra_chan,
                           const SPChannel& ket_chan);

  const SPChannel& BraChannel() const { return bra_chan_; }
  const SPChannel& KetChannel() const { return ket_chan_; }
  Scalar1BChannelKey ChannelKey() const { return full_chan_key_; }

  void swap(Scalar1BChannel& other) noexcept {
    using std::swap;
    swap(bra_chan_, other.bra_chan_);
    swap(ket_chan_, other.ket_chan_);
    swap(full_chan_key_, other.full_chan_key_);
  }

 private:
  SPChannel bra_chan_;
  SPChannel ket_chan_;
  Scalar1BChannelKey full_chan_key_;
};

inline void swap(Scalar1BChannel& a, Scalar1BChannel& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_CHANNEL_H_
