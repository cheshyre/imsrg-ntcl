// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/model_space.h"

#include <memory>
#include <utility>
#include <vector>

#include "imsrg/model_space/scalar/one_body/channel.h"
#include "imsrg/model_space/single_particle/model_space.h"

namespace imsrg {
std::shared_ptr<const Scalar1BModelSpace> Scalar1BModelSpace::FromSPModelSpace(
    const SPModelSpace& sp_ms) {
  const auto& sp_chans = sp_ms.Channels();
  std::vector<Scalar1BChannel> chans;
  chans.reserve(sp_chans.size());

  for (const auto& sp_chan : sp_chans) {
    chans.emplace_back(sp_chan, sp_chan);
  }

  return std::make_shared<const Scalar1BModelSpace>(std::move(chans));
}

Scalar1BModelSpace::Scalar1BModelSpace(std::vector<Scalar1BChannel>&& chans)
    : chans_(std::move(chans)) {}
}  // namespace imsrg
