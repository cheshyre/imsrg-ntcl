// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/model_space.h"

#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/one_body/channel.h"
#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/model_space/single_particle/model_space.h"

namespace imsrg {

namespace detail {
static absl::flat_hash_map<imsrg::Scalar1BChannelKey, std::size_t>
GenerateChannelIndexLookup(const std::vector<imsrg::Scalar1BChannel>& chans);
}

bool Scalar1BModelSpace::IsChannelInModelSpace(
    Scalar1BChannelKey chankey) const {
  const auto search = chan_index_lookup_.find(chankey);
  return search != chan_index_lookup_.end();
}

std::size_t Scalar1BModelSpace::IndexOfChannelInModelSpace(
    Scalar1BChannelKey chankey) const {
  // Expects(IsChannelInModelSpace(chankey));
  // ^ We check this later
  const auto search = chan_index_lookup_.find(chankey);
  Expects(search != chan_index_lookup_.end());

  return search->second;
}

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
    : chans_(std::move(chans)),
      chan_index_lookup_(imsrg::detail::GenerateChannelIndexLookup(chans_)) {}

namespace detail {

absl::flat_hash_map<imsrg::Scalar1BChannelKey, std::size_t>
GenerateChannelIndexLookup(const std::vector<imsrg::Scalar1BChannel>& chans) {
  absl::flat_hash_map<imsrg::Scalar1BChannelKey, std::size_t> index_lookup;
  index_lookup.reserve(chans.size());

  for (std::size_t index = 0; index < chans.size(); index += 1) {
    index_lookup[chans[index].ChannelKey()] = index;
  }
  return index_lookup;
}
}  // namespace detail
}  // namespace imsrg
