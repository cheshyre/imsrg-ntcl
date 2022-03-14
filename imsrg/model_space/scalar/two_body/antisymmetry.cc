// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/antisymmetry.h"

#include <array>

#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/quantum_numbers/coupling/phases.h"

namespace imsrg {
bool IsChannelInMinimalAntisymmetricSet(const Scalar2BChannelKey& chankey) {
  return (chankey.BraChannelKey().p_chan_key.Index() >=
          chankey.BraChannelKey().q_chan_key.Index()) &&
         (chankey.KetChannelKey().p_chan_key.Index() >=
          chankey.KetChannelKey().q_chan_key.Index());
}

std::array<Scalar2BChannelKey, 3> GeneratePermutedChannels(
    const Scalar2BChannelKey& chankey) {
  const auto [chankey_p, chankey_q] = chankey.BraChannelKey();
  const auto [chankey_r, chankey_s] = chankey.KetChannelKey();

  const auto jj_2b = chankey.OpChannel().JJ();

  return {
      Scalar2BChannelKey({chankey_q, chankey_p}, {chankey_r, chankey_s}, jj_2b),
      Scalar2BChannelKey({chankey_p, chankey_q}, {chankey_s, chankey_r}, jj_2b),
      Scalar2BChannelKey({chankey_q, chankey_p}, {chankey_s, chankey_r},
                         jj_2b)};
}

std::array<int, 3> GeneratePermutationFactors(
    const Scalar2BChannelKey& chankey) {
  const auto [chankey_p, chankey_q] = chankey.BraChannelKey();
  const auto [chankey_r, chankey_s] = chankey.KetChannelKey();
  const auto jj_p = chankey_p.JJ();
  const auto jj_q = chankey_q.JJ();
  const auto jj_r = chankey_r.JJ();
  const auto jj_s = chankey_s.JJ();

  const auto jj_2b = chankey.OpChannel().JJ();

  std::array<int, 3> phases = {
      -1 * (Phase(jj_p) * Phase(jj_q) * Phase(jj_2b, -1)).AsInt(),
      -1 * (Phase(jj_r) * Phase(jj_s) * Phase(jj_2b, -1)).AsInt(),
      (Phase(jj_p) * Phase(jj_q) * Phase(jj_r) * Phase(jj_s)).AsInt()};

  return phases;
}
}  // namespace imsrg
