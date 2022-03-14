// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/model_space.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "imsrg/assert.h"
#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/partial_basis.h"

namespace imsrg {

namespace detail {
static std::vector<imsrg::SPChannel> SortChannels(
    const std::vector<SPChannel>& chans);
static std::size_t DetermineMaxIndex(
    const std::vector<imsrg::SPChannel>& chans);
static std::vector<imsrg::SPChannelKey> ExtractChannelKeys(
    const std::vector<SPChannel>& chans);
static std::vector<bool> ExtractDefined(const std::vector<SPChannel>& chans,
                                        std::size_t max_index);
static std::vector<std::size_t> ExtractDims(const std::vector<SPChannel>& chans,
                                            std::size_t max_index);
static std::vector<std::vector<double>> ExtractOccs(
    const std::vector<SPChannel>& chans, std::size_t max_index);
static std::vector<std::vector<double>> ExtractOccsBar(
    const std::vector<SPChannel>& chans, std::size_t max_index);
}  // namespace detail

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
    : chans_(imsrg::detail::SortChannels(chans)),
      max_index_(imsrg::detail::DetermineMaxIndex(chans_)),
      chankeys_(imsrg::detail::ExtractChannelKeys(chans_)),
      defined_(imsrg::detail::ExtractDefined(chans_, max_index_)),
      dims_(imsrg::detail::ExtractDims(chans_, max_index_)),
      occs_(imsrg::detail::ExtractOccs(chans_, max_index_)),
      occs_bar_(imsrg::detail::ExtractOccsBar(chans_, max_index_)) {
  // Expects(chans are unique)
  // Ensures(chans are sorted)
}

std::size_t SPModelSpace::ChannelDim(SPChannelKey chankey) const {
  Expects(IsChannelInModelSpace(chankey));
  return dims_[chankey.Index()];
}

const std::vector<double>& SPModelSpace::Occs(SPChannelKey chankey) const {
  Expects(IsChannelInModelSpace(chankey));
  return occs_[chankey.Index()];
}

const std::vector<double>& SPModelSpace::OccsBar(SPChannelKey chankey) const {
  Expects(IsChannelInModelSpace(chankey));
  return occs_bar_[chankey.Index()];
}

namespace detail {
std::vector<imsrg::SPChannel> SortChannels(
    const std::vector<SPChannel>& chans) {
  std::vector<imsrg::SPChannel> chans_copy(chans);
  std::sort(chans_copy.begin(), chans_copy.end());
  return chans_copy;
}

std::size_t DetermineMaxIndex(const std::vector<imsrg::SPChannel>& chans) {
  Expects(chans.size() > 0);
  std::size_t max_index = 0;
  for (const auto& chan : chans) {
    max_index = std::max(max_index, chan.Index());
  }
  return max_index;
}

std::vector<imsrg::SPChannelKey> ExtractChannelKeys(
    const std::vector<SPChannel>& chans) {
  std::vector<imsrg::SPChannelKey> chankeys;
  chankeys.reserve(chans.size());

  for (const auto& chan : chans) {
    chankeys.push_back(chan.ChannelKey());
  }

  return chankeys;
}

std::vector<bool> ExtractDefined(const std::vector<SPChannel>& chans,
                                 std::size_t max_index) {
  std::vector<bool> defined(max_index + 1, false);

  for (const auto& chan : chans) {
    const auto index = chan.Index();
    Expects(!defined[index]);
    defined[index] = true;
  }

  return defined;
}

std::vector<std::size_t> ExtractDims(const std::vector<SPChannel>& chans,
                                     std::size_t max_index) {
  std::vector<std::size_t> sizes(max_index + 1, 0);

  for (const auto& chan : chans) {
    const auto index = chan.Index();
    sizes[index] = chan.size();
  }
  return sizes;
}

std::vector<std::vector<double>> ExtractOccs(
    const std::vector<SPChannel>& chans, std::size_t max_index) {
  std::vector<std::vector<double>> occs(max_index + 1);

  for (const auto& chan : chans) {
    const auto index = chan.Index();
    occs[index] = chan.ChannelBasis().Occs();
  }
  return occs;
}

std::vector<std::vector<double>> ExtractOccsBar(
    const std::vector<SPChannel>& chans, std::size_t max_index) {
  std::vector<std::vector<double>> occs(max_index + 1);

  for (const auto& chan : chans) {
    const auto index = chan.Index();
    occs[index] = chan.ChannelBasis().OccsBar();
  }
  return occs;
}
}  // namespace detail

}  // namespace imsrg
