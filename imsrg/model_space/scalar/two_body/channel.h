// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_H_

#include <utility>

#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/scalar/two_body/state_channel.h"
#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

class Scalar2BChannel {
 public:
  explicit Scalar2BChannel(const Scalar2BStateChannel& bra_chan,
                           const Scalar2BStateChannel& ket_chan,
                           TotalAngMom jj_2b);

  const Scalar2BStateChannel& BraStateChannel() const { return bra_chan_; }
  const Scalar2BStateChannel& KetStateChannel() const { return ket_chan_; }
  const SPChannel& BraChannel1() const { return bra_chan_.p_chan; }
  const SPChannel& BraChannel2() const { return bra_chan_.q_chan; }
  const SPChannel& KetChannel1() const { return ket_chan_.p_chan; }
  const SPChannel& KetChannel2() const { return ket_chan_.q_chan; }
  Scalar2BChannelKey ChannelKey() const { return full_chan_key_; }

  void swap(Scalar2BChannel& other) noexcept {
    using std::swap;
    swap(bra_chan_, other.bra_chan_);
    swap(ket_chan_, other.ket_chan_);
    swap(full_chan_key_, other.full_chan_key_);
  }

 private:
  Scalar2BStateChannel bra_chan_;
  Scalar2BStateChannel ket_chan_;
  Scalar2BChannelKey full_chan_key_;
};

inline void swap(Scalar2BChannel& a, Scalar2BChannel& b) noexcept { a.swap(b); }
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_CHANNEL_H_
