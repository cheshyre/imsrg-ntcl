// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/full_basis.h"

#include <vector>

#include "imsrg/model_space/basis/states.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
SPFullBasis SPFullBasis::FromEMax(HOEnergy emax) {
  std::vector<SPState> states;

  for (const auto e : GenerateHOEnergyShells(emax)) {
    for (const auto [n, l] : e.GenerateSubShellQuantumNumbers()) {
      for (const auto jj :
           GenerateCouplingRange<TotalAngMom>(l, Spin::OneHalf())) {
        for (const auto m_tt :
             {IsospinProj::Neutron(), IsospinProj::Proton()}) {
          states.push_back(SPState(n, l, jj, m_tt));
        }
      }
    }
  }

  return SPFullBasis(states);
}
}  // namespace imsrg
