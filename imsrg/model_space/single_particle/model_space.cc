// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/model_space.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/partial_basis.h"

namespace imsrg {
std::shared_ptr<const SPModelSpace> SPModelSpace::FromFullBasis(
    const SPFullBasis& full_basis) {
  const auto basis_part = PartitionSPFullBasisIntoSPPartialBases(full_basis);

  std::vector<SPChannel> chans;
  chans.reserve(basis_part.size());
  for (const auto& [jjpmtt, basis_ptr] : basis_part) {
    chans.emplace_back(SPChannelKey(jjpmtt), basis_ptr);
  }

  return std::make_shared<const SPModelSpace>(chans);
}

SPModelSpace::SPModelSpace(const std::vector<SPChannel>& chans)
    : chans_(chans) {
  // Expects(chans are unique)
  // Sort channels in order of increasing index
  std::sort(chans_.begin(), chans_.end());
  // Ensures(chans are sorted)
}

}  // namespace imsrg
