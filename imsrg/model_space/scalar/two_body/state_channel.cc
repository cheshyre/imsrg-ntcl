// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/state_channel.h"

#include <utility>

#include "imsrg/model_space/single_particle/channel.h"

namespace imsrg {

void swap(Scalar2BStateChannel& a, Scalar2BStateChannel& b) noexcept {
  using std::swap;
  swap(a.p_chan, b.p_chan);
  swap(a.q_chan, b.q_chan);
}

}  // namespace imsrg
