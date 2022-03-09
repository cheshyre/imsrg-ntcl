// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/model_space.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/bare_channel_key.h"
#include "imsrg/model_space/scalar/two_body/channel.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/scalar/two_body/state_channel_key.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
static absl::flat_hash_map<imsrg::Scalar2BChannelKey, std::size_t>
GenerateChannelIndexLookup(const std::vector<imsrg::Scalar2BChannel>& chans);

static absl::flat_hash_map<imsrg::Scalar2BOpChannel,
                           std::vector<imsrg::Scalar2BStateChannelKey>>
Generate2BStateKeyLookup(const imsrg::SPModelSpace& sp_ms);

static std::vector<imsrg::Scalar2BBareChannelKey> GenerateBareChannels(
    const imsrg::SPModelSpace& sp_ms);
}  // namespace detail

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

const std::vector<Scalar2BStateChannelKey>&
Scalar2BModelSpace::GetStateChannelsInOperatorChannel(
    Scalar2BOpChannel op_chan) const {
  const auto search = state_keys_lookup_.find(op_chan);
  Expects(search != state_keys_lookup_.end());
  return search->second;
}

std::shared_ptr<const Scalar2BModelSpace> Scalar2BModelSpace::FromSPModelSpace(
    const std::shared_ptr<const SPModelSpace>& sp_ms) {
  const auto& sp_chans = sp_ms->Channels();
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
  return std::make_shared<const Scalar2BModelSpace>(
      sp_ms, std::move(chans), imsrg::detail::Generate2BStateKeyLookup(*sp_ms),
      imsrg::detail::GenerateBareChannels(*sp_ms));
}

Scalar2BModelSpace::Scalar2BModelSpace(
    const std::shared_ptr<const SPModelSpace>& sp_ms,
    std::vector<Scalar2BChannel>&& chans,
    absl::flat_hash_map<Scalar2BOpChannel,
                        std::vector<Scalar2BStateChannelKey>>&&
        state_keys_lookup,
    std::vector<Scalar2BBareChannelKey>&& sp_chans)
    : sp_ms_(sp_ms),
      chans_(std::move(chans)),
      chan_index_lookup_(imsrg::detail::GenerateChannelIndexLookup(chans_)),
      state_keys_lookup_(std::move(state_keys_lookup)),
      sp_chans_(std::move(sp_chans)) {}

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

absl::flat_hash_map<imsrg::Scalar2BOpChannel,
                    std::vector<imsrg::Scalar2BStateChannelKey>>
Generate2BStateKeyLookup(const imsrg::SPModelSpace& sp_ms) {
  absl::flat_hash_map<imsrg::Scalar2BOpChannel,
                      std::vector<imsrg::Scalar2BStateChannelKey>>
      state_key_lookup;

  const auto& sp_chans = sp_ms.Channels();

  for (const auto& chan_p : sp_chans) {
    for (const auto& chan_q : sp_chans) {
      // p, q coupling range
      const auto jj_pq_min =
          CouplingMinimum<TotalAngMom>(chan_p.JJ(), chan_q.JJ());
      const auto jj_pq_max =
          CouplingMaximum<TotalAngMom>(chan_p.JJ(), chan_q.JJ());

      const auto parity_pq = chan_p.P() + chan_q.P();
      const auto m_tt_pq = chan_p.M_TT() + chan_q.M_TT();

      const imsrg::Scalar2BStateChannelKey state_chankey = {
          chan_p.ChannelKey(), chan_q.ChannelKey()};

      for (const auto jj_pq :
           CouplingRangeFromMinAndMax(jj_pq_min, jj_pq_max)) {
        const imsrg::Scalar2BOpChannel op_chan(jj_pq, parity_pq, m_tt_pq);

        state_key_lookup[op_chan].push_back(state_chankey);
      }
    }
  }
  return state_key_lookup;
}

std::vector<imsrg::Scalar2BBareChannelKey> GenerateBareChannels(
    const imsrg::SPModelSpace& sp_ms) {
  std::vector<imsrg::Scalar2BBareChannelKey> bare_chans;
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
          if (jj_max >= jj_min) {
            bare_chans.push_back(Scalar2BBareChannelKey{
                chan_p.ChannelKey(), chan_q.ChannelKey(), chan_r.ChannelKey(),
                chan_s.ChannelKey()});
          }
        }
      }
    }
  }
  return bare_chans;
}

}  // namespace detail

}  // namespace imsrg
