// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_FULL_BASIS_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_FULL_BASIS_H_

#include <utility>
#include <vector>

#include "imsrg/model_space/single_particle/reference_state.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/ho_energy.h"

namespace imsrg {

class SPFullBasis {
 public:
  static SPFullBasis FromEMax(HOEnergy emax);

  static SPFullBasis FromEMaxAndReferenceState(HOEnergy emax,
                                               const ReferenceState& ref);

  explicit SPFullBasis(const std::vector<SPState>& states) : states_(states) {}

  // Default copy, move, and destructor

  std::size_t size() const { return states_.size(); }

  SPState at(std::size_t index) const { return states_[index]; }

  void swap(SPFullBasis& other) noexcept {
    using std::swap;
    swap(states_, other.states_);
  }

 private:
  std::vector<SPState> states_;
};

inline void swap(SPFullBasis& a, SPFullBasis& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_FULL_BASIS_H_
