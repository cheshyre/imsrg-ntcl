// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_H_

#include <utility>

#include "imsrg/model_space/single_particle/channel.h"

namespace imsrg {
struct Scalar2BStateChannel {
  SPChannel p_chan;
  SPChannel q_chan;
};

void swap(Scalar2BStateChannel& a, Scalar2BStateChannel& b) noexcept;
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_H_
