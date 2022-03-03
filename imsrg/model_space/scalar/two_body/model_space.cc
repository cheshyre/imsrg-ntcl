// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/model_space.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/channel.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
static absl::flat_hash_map<imsrg::Scalar2BChannelKey, std::size_t>
GenerateChannelIndexLookup(const std::vector<imsrg::Scalar2BChannel>& chans);
}

bool Scalar2BModelSpace::IsChannelInModelSpace(
    Scalar2BChannelKey chankey) const {
  const auto search = chan_index_lookup_.find(chankey);
  return search != chan_index_lookup_.end();
}

std::size_t Scalar2BModelSpace::IndexOfChannelInModelSpace(
    Scalar2BChannelKey chankey) const {
  // Expects(IsChannelInModelSpace(chankey));
  // ^ We check this later
  const auto search = chan_index_lookup_.find(chankey);
  Expects(search != chan_index_lookup_.end());

  return search->second;
}

std::shared_ptr<const Scalar2BModelSpace> Scalar2BModelSpace::FromSPModelSpace(
    const SPModelSpace& sp_ms) {
  const auto& sp_chans = sp_ms.Channels();
  std::vector<Scalar2BChannel> chans;

  for (const auto& chan_p : sp_chans) {
    for (const auto& chan_q : sp_chans) {
      // if (chan_q.Index() > chan_p.Index()) {
      //   continue;
      // }
      // p, q coupling range
      const auto jj_pq_min =
          CouplingMinimum<TotalAngMom>(chan_p.JJ(), chan_q.JJ());
      const auto jj_pq_max =
          CouplingMaximum<TotalAngMom>(chan_p.JJ(), chan_q.JJ());
      for (const auto& chan_r : sp_chans) {
        for (const auto& chan_s : sp_chans) {
          // if (chan_s.Index() > chan_r.Index()) {
          //   continue;
          // }
          // Parity conservation
          if (chan_p.P() + chan_q.P() != chan_r.P() + chan_s.P()) {
            continue;
          }
          // Isospin conservation
          if (chan_p.M_TT() + chan_q.M_TT() != chan_r.M_TT() + chan_s.M_TT()) {
            continue;
          }

          // r, s coupling range
          const auto jj_rs_min =
              CouplingMinimum<TotalAngMom>(chan_r.JJ(), chan_s.JJ());
          const auto jj_rs_max =
              CouplingMaximum<TotalAngMom>(chan_r.JJ(), chan_s.JJ());

          // Overlapping coupling range
          const auto jj_min = std::max(jj_pq_min, jj_rs_min);
          const auto jj_max = std::min(jj_pq_max, jj_rs_max);
          if (jj_max < jj_min) {
            continue;
          }

          for (const auto jj_2b : CouplingRangeFromMinAndMax(jj_min, jj_max)) {
            chans.push_back(
                Scalar2BChannel({chan_p, chan_q}, {chan_r, chan_s}, jj_2b));
          }
        }
      }
    }
  }
  return std::make_shared<const Scalar2BModelSpace>(std::move(chans));
}

Scalar2BModelSpace::Scalar2BModelSpace(std::vector<Scalar2BChannel>&& chans)
    : chans_(std::move(chans)),
      chan_index_lookup_(imsrg::detail::GenerateChannelIndexLookup(chans_)) {}

namespace detail {

absl::flat_hash_map<imsrg::Scalar2BChannelKey, std::size_t>
GenerateChannelIndexLookup(const std::vector<imsrg::Scalar2BChannel>& chans) {
  absl::flat_hash_map<imsrg::Scalar2BChannelKey, std::size_t> index_lookup;
  index_lookup.reserve(chans.size());

  for (std::size_t index = 0; index < chans.size(); index += 1) {
    index_lookup[chans[index].ChannelKey()] = index;
  }
  return index_lookup;
}
}  // namespace detail

}  // namespace imsrg
