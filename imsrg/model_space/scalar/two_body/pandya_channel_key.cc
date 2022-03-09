// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/pandya_channel_key.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/bare_channel_key.h"
#include "imsrg/model_space/scalar/two_body/pandya_operator_channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
static imsrg::Scalar2BPanydaOpChannel CreateOpChan(
    imsrg::Scalar2BBareChannelKey sp_chankeys, imsrg::TotalAngMom jj_2b);
}

Scalar2BPandyaChannelKey::Scalar2BPandyaChannelKey(SPChannelKey chankey_p,
                                                   SPChannelKey chankey_q,
                                                   SPChannelKey chankey_r,
                                                   SPChannelKey chankey_s,
                                                   TotalAngMom jj_2b)
    : sp_chankeys_{chankey_p, chankey_q, chankey_r, chankey_s},
      op_chan_(imsrg::detail::CreateOpChan(sp_chankeys_, jj_2b)) {}

Scalar2BPandyaChannelKey::Scalar2BPandyaChannelKey(
    Scalar2BBareChannelKey bare_chankey, TotalAngMom jj_2b)
    : sp_chankeys_(bare_chankey),
      op_chan_(imsrg::detail::CreateOpChan(sp_chankeys_, jj_2b)) {}

std::vector<Scalar2BChannelKey> Scalar2BPandyaChannelKey::StandardChannels()
    const {
  Scalar2BBareChannelKey normal_channel_key = {
      sp_chankeys_.chankey_1, sp_chankeys_.chankey_4, sp_chankeys_.chankey_3,
      sp_chankeys_.chankey_2};

  auto jj12_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
      normal_channel_key.chankey_1.JJ(), normal_channel_key.chankey_2.JJ());
  auto jj34_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
      normal_channel_key.chankey_3.JJ(), normal_channel_key.chankey_4.JJ());
  auto jj12_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
      normal_channel_key.chankey_1.JJ(), normal_channel_key.chankey_2.JJ());
  auto jj34_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
      normal_channel_key.chankey_3.JJ(), normal_channel_key.chankey_4.JJ());

  const auto range = imsrg::CouplingRangeFromMinAndMax(
      std::max(jj12_min, jj34_min), std::min(jj12_max, jj34_max));

  std::vector<Scalar2BChannelKey> chans;

  for (const auto& x : range) {
    chans.push_back(Scalar2BChannelKey(
        {normal_channel_key.chankey_1, normal_channel_key.chankey_2},
        {normal_channel_key.chankey_3, normal_channel_key.chankey_4}, x));
  }

  return chans;
}

bool operator==(const Scalar2BPandyaChannelKey& a,
                const Scalar2BPandyaChannelKey& b) {
  return (a.SingleParticleChannels() == b.SingleParticleChannels()) &&
         (a.OperatorChannel() == b.OperatorChannel());
}

std::vector<Scalar2BPandyaChannelKey> GeneratePandyaChannels(
    Scalar2BBareChannelKey bare_chankey) {
  auto jj12_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
      bare_chankey.chankey_1.JJ(), bare_chankey.chankey_2.JJ());
  auto jj34_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
      bare_chankey.chankey_3.JJ(), bare_chankey.chankey_4.JJ());
  auto jj12_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
      bare_chankey.chankey_1.JJ(), bare_chankey.chankey_2.JJ());
  auto jj34_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
      bare_chankey.chankey_3.JJ(), bare_chankey.chankey_4.JJ());

  const auto range = imsrg::CouplingRangeFromMinAndMax(
      std::max(jj12_min, jj34_min), std::min(jj12_max, jj34_max));
  std::vector<Scalar2BPandyaChannelKey> chans;
  chans.reserve(range.size());

  for (const auto& x : range) {
    chans.emplace_back(bare_chankey, x);
  }

  return chans;
}

namespace detail {
static imsrg::Scalar2BPanydaOpChannel CreateOpChan(
    imsrg::Scalar2BBareChannelKey sp_chankeys, imsrg::TotalAngMom jj_2b) {
  Expects(sp_chankeys.chankey_1.P() - sp_chankeys.chankey_2.P() ==
          sp_chankeys.chankey_3.P() - sp_chankeys.chankey_4.P());
  Expects(sp_chankeys.chankey_1.M_TT() - sp_chankeys.chankey_2.M_TT() ==
          sp_chankeys.chankey_3.M_TT() - sp_chankeys.chankey_4.M_TT());
  Expects(jj_2b >= imsrg::CouplingMinimum<imsrg::TotalAngMom>(
                       sp_chankeys.chankey_1.JJ(), sp_chankeys.chankey_2.JJ()));
  Expects(jj_2b >= imsrg::CouplingMinimum<imsrg::TotalAngMom>(
                       sp_chankeys.chankey_3.JJ(), sp_chankeys.chankey_4.JJ()));
  Expects(jj_2b <= imsrg::CouplingMaximum<imsrg::TotalAngMom>(
                       sp_chankeys.chankey_1.JJ(), sp_chankeys.chankey_2.JJ()));
  Expects(jj_2b <= imsrg::CouplingMaximum<imsrg::TotalAngMom>(
                       sp_chankeys.chankey_3.JJ(), sp_chankeys.chankey_4.JJ()));

  return imsrg::Scalar2BPanydaOpChannel(
      jj_2b, sp_chankeys.chankey_1.P() - sp_chankeys.chankey_2.P(),
      sp_chankeys.chankey_1.M_TT() - sp_chankeys.chankey_2.M_TT());
}
}  // namespace detail

}  // namespace imsrg
