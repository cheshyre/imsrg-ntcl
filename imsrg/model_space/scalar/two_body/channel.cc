// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/channel.h"

#include <utility>

#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/scalar/two_body/state_channel.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

Scalar2BChannel::Scalar2BChannel(const Scalar2BStateChannel& bra_chan,
                                 const Scalar2BStateChannel& ket_chan,
                                 TotalAngMom jj_2b)
    : bra_chan_(bra_chan),
      ket_chan_(ket_chan),
      full_chan_key_(
          {bra_chan_.p_chan.ChannelKey(), bra_chan_.q_chan.ChannelKey()},
          {ket_chan_.p_chan.ChannelKey(), ket_chan_.q_chan.ChannelKey()},
          jj_2b) {}

}  // namespace imsrg
