// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/channel_key.h"

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/one_body/operator_channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"

namespace imsrg {
Scalar1BChannelKey::Scalar1BChannelKey(SPChannelKey chan_key_bra,
                                       SPChannelKey chan_key_ket)
    : bra_chan_key_(chan_key_bra),
      ket_chan_key_(chan_key_ket),
      op_chan_(GenerateOpChannel(bra_chan_key_, ket_chan_key_)) {
  Expects(bra_chan_key_ == ket_chan_key_);
  Ensures(op_chan_.JJ() == bra_chan_key_.JJ());
  Ensures(op_chan_.P() == bra_chan_key_.P());
  Ensures(op_chan_.M_TT() == bra_chan_key_.M_TT());
}

Scalar1BOpChannel Scalar1BChannelKey::GenerateOpChannel(
    const SPChannelKey& bra_chan_key, const SPChannelKey& ket_chan_key) {
  Expects(bra_chan_key == ket_chan_key);

  return Scalar1BOpChannel(bra_chan_key.JJ(), bra_chan_key.P(),
                           bra_chan_key.M_TT());
}

bool operator==(const Scalar1BChannelKey& a, const Scalar1BChannelKey& b) {
  return ((a.BraChannelKey() == b.BraChannelKey()) &&
          (a.KetChannelKey() == b.KetChannelKey()) &&
          (a.OpChannel() == b.OpChannel()));
}
}  // namespace imsrg
