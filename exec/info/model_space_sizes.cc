// Copyright 2022 Matthias Heinz

#include <string>
#include <vector>

#include "spdlog/spdlog.h"

#include "imsrg/quantum_numbers/ho_energy.h"

#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/model_space/single_particle/partial_basis.h"
#include "imsrg/model_space/single_particle/state.h"

#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/model_space/scalar/two_body/model_space.h"

int main(void) {
  const std::string filler(72, '*');
  using imsrg::HOEnergy;
  for (const auto emax : {HOEnergy(2), HOEnergy(4), HOEnergy(6), HOEnergy(8),
                          HOEnergy(10), HOEnergy(12), HOEnergy(14)}) {
    spdlog::info(filler);
    spdlog::info("Emax = {}", emax.AsInt());
    spdlog::info(filler);

    const auto full_basis = imsrg::SPFullBasis::FromEMax(emax);
    spdlog::info("Single-particle basis size = {} states", full_basis.size());
    spdlog::info("size in memory = {}",
                 full_basis.size() * sizeof(imsrg::SPState));
    spdlog::info(filler);

    const auto basis_part =
        imsrg::PartitionSPFullBasisIntoSPPartialBases(full_basis);
    std::vector<imsrg::SPChannel> chans;
    chans.reserve(basis_part.size());
    for (const auto& [jjpmtt, basis_ptr] : basis_part) {
      chans.emplace_back(imsrg::SPChannelKey(jjpmtt), basis_ptr);
    }
    const imsrg::SPModelSpace sp_ms(chans);

    spdlog::info("Single-particle model space size = {} channels",
                 sp_ms.Channels().size());
    spdlog::info("size in memory = {}",
                 sp_ms.Channels().size() * sizeof(imsrg::SPChannel));
    spdlog::info(filler);

    const auto& ms1b = imsrg::Scalar1BModelSpace::FromSPModelSpace(sp_ms);
    spdlog::info("One-body model space size = {} channels",
                 ms1b->NumberOfChannels());
    spdlog::info("size in memory = {}",
                 ms1b->NumberOfChannels() * sizeof(imsrg::Scalar1BChannel));
    spdlog::info(filler);

    const auto& ms2b = imsrg::Scalar2BModelSpace::FromSPModelSpace(sp_ms);
    spdlog::info("Two-body model space size = {} channels",
                 ms2b->NumberOfChannels());
    spdlog::info("size in memory = {}",
                 ms2b->NumberOfChannels() * sizeof(imsrg::Scalar2BChannel));
    spdlog::info(filler);
  }

  return 0;
}
