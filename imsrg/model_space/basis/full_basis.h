// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_FULL_BASIS_H_
#define IMSRG_MODEL_SPACE_BASIS_FULL_BASIS_H_

#include <utility>
#include <vector>

#include "imsrg/model_space/basis/states.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

class SPFullBasis {
 private:
  std::vector<SPState> states_;

 public:
  explicit SPFullBasis(const std::vector<SPState>& states) : states_(states) {}

  static SPFullBasis FromEMax(HOEnergy emax) {
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

  // TODO(mheinz): implement factory method that includes reference state
  // information

  // Default copy, move, and destructor

  std::size_t size() const { return states_.size(); }

  SPState at(std::size_t index) const { return states_[index]; }

  void swap(SPFullBasis& other) noexcept {
    using std::swap;

    swap(states_, other.states_);
  }
};

inline void swap(SPFullBasis& a, SPFullBasis& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_BASIS_FULL_BASIS_H_
