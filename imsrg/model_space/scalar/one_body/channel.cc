// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/channel.h"

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/model_space/single_particle/channel.h"

namespace imsrg {

Scalar1BChannel::Scalar1BChannel(const SPChannel& bra_chan,
                                 const SPChannel& ket_chan)
    : bra_chan_(bra_chan),
      ket_chan_(ket_chan),
      full_chan_key_(bra_chan_.ChannelKey(), ket_chan_.ChannelKey()) {
  Expects(bra_chan_ == ket_chan_);
}

}  // namespace imsrg
