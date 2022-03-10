// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_CHANNEL_KEY_H_

#include <utility>
#include <vector>

#include "imsrg/model_space/scalar/two_body/bare_channel_key.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/scalar/two_body/pandya_operator_channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

class Scalar2BPandyaChannelKey {
 public:
  explicit Scalar2BPandyaChannelKey(SPChannelKey chankey_p,
                                    SPChannelKey chankey_q,
                                    SPChannelKey chankey_r,
                                    SPChannelKey chankey_s, TotalAngMom jj_2b);

  explicit Scalar2BPandyaChannelKey(Scalar2BBareChannelKey bare_chankey,
                                    TotalAngMom jj_2b);

  // Default copy, move, dtor

  Scalar2BBareChannelKey SingleParticleChannels() const { return sp_chankeys_; }
  Scalar2BPandyaOpChannel OperatorChannel() const { return op_chan_; }

  std::vector<Scalar2BChannelKey> StandardChannels() const;

  void swap(Scalar2BPandyaChannelKey& other) noexcept {
    using std::swap;
    swap(sp_chankeys_, other.sp_chankeys_);
    swap(op_chan_, other.op_chan_);
  }

 private:
  Scalar2BBareChannelKey sp_chankeys_;
  Scalar2BPandyaOpChannel op_chan_;
};

inline void swap(Scalar2BPandyaChannelKey& a,
                 Scalar2BPandyaChannelKey& b) noexcept {
  a.swap(b);
}

bool operator==(const Scalar2BPandyaChannelKey& a,
                const Scalar2BPandyaChannelKey& b);

inline bool operator!=(const Scalar2BPandyaChannelKey& a,
                       const Scalar2BPandyaChannelKey& b) {
  return !(a == b);
}

std::vector<Scalar2BPandyaChannelKey> GeneratePandyaChannels(
    Scalar2BBareChannelKey bare_chankey);

Scalar2BBareChannelKey BareChannelKeyPandyaSwap(
    Scalar2BBareChannelKey sp_chans);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_PANDYA_CHANNEL_KEY_H_
