// Copyright 2022 Matthias Heinz

#include <string>

#include "spdlog/spdlog.h"

#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/m_jj.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/occupation_number.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/model_space/single_particle/partial_basis.h"
#include "imsrg/model_space/single_particle/state.h"

#include "imsrg/model_space/scalar/one_body/channel.h"
#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/model_space/scalar/one_body/operator_channel.h"

int main(void) {
  std::string filler(72, '*');

  spdlog::info(filler);
  spdlog::info("Sizes of imsrg objects");
  spdlog::info(filler);
  spdlog::info("Quantum numbers");
  spdlog::info(filler);
  spdlog::info("JJ = {}", sizeof(imsrg::JJ));
  spdlog::info("M_JJ = {}", sizeof(imsrg::M_JJ));
  spdlog::info("HOEnergy = {}", sizeof(imsrg::HOEnergy));
  spdlog::info("Isospin = {}", sizeof(imsrg::Isospin));
  spdlog::info("IsospinProj = {}", sizeof(imsrg::IsospinProj));
  spdlog::info("OccupationNumber = {}", sizeof(imsrg::OccupationNumber));
  spdlog::info("OrbitalAngMom = {}", sizeof(imsrg::OrbitalAngMom));
  spdlog::info("Parity = {}", sizeof(imsrg::Parity));
  spdlog::info("RadialExcitationNumber = {}",
               sizeof(imsrg::RadialExcitationNumber));
  spdlog::info("Spin = {}", sizeof(imsrg::Spin));
  spdlog::info("TotalAngMom = {}", sizeof(imsrg::TotalAngMom));

  spdlog::info(filler);
  spdlog::info("Modelspace details");
  spdlog::info(filler);
  spdlog::info("Single-particle basis");
  spdlog::info(filler);
  spdlog::info("SPState = {}", sizeof(imsrg::SPState));
  spdlog::info("SPFullBasis = {}", sizeof(imsrg::SPFullBasis));
  spdlog::info("SPPartialBasis = {}", sizeof(imsrg::SPPartialBasis));
  spdlog::info("SPChannelKey = {}", sizeof(imsrg::SPChannelKey));
  spdlog::info("SPChannel = {}", sizeof(imsrg::SPChannel));
  spdlog::info("SPModelSpace = {}", sizeof(imsrg::SPModelSpace));
  spdlog::info(filler);
  spdlog::info("Scalar 1-body model space");
  spdlog::info(filler);
  spdlog::info("Scalar1BOpChannel = {}", sizeof(imsrg::Scalar1BOpChannel));
  spdlog::info("Scalar1BChannelKey = {}", sizeof(imsrg::Scalar1BChannelKey));
  spdlog::info("Scalar1BChannel = {}", sizeof(imsrg::Scalar1BChannel));
  spdlog::info("Scalar1BModelSpace = {}", sizeof(imsrg::Scalar1BModelSpace));

  return 0;
}
