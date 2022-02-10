// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/sp_model_space.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "imsrg/model_space/basis/sp_channel.h"

namespace imsrg {
SPModelSpace::SPModelSpace(const std::vector<SPChannel>& chans)
    : chans_(chans) {
  // Expects(chans are unique)
  // Sort channels in order of increasing index
  std::sort(chans_.begin(), chans_.end());
  // Ensures(chans are sorted)
}

}  // namespace imsrg
