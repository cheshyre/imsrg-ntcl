// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/ho_energy.h"

#include <utility>
#include <vector>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"

namespace imsrg {

std::vector<N_L> HOEnergy::GenerateSubShellQuantumNumbers() const {
  std::vector<N_L> shells;
  shells.reserve(e_ / 2 + 1);
  for (int n = 0; n <= e_ / 2; n++) {
    int l = e_ - 2 * n;
    shells.push_back({RadialExcitationNumber(n), OrbitalAngMom(l)});
  }
  return shells;
}

std::vector<HOEnergy> GenerateHOEnergyShells(HOEnergy emax) {
  std::vector<HOEnergy> shells;
  shells.reserve(emax.AsInt() + 1);

  for (int e = 0; HOEnergy(e) <= emax; e++) {
    shells.push_back(HOEnergy(e));
  }

  return shells;
}

}  // namespace imsrg
