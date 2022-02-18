// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_REFERENCE_STATE_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_REFERENCE_STATE_H_

#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/error.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/model_space/single_particle/state_key.h"
#include "imsrg/model_space/single_particle/state_string.h"
#include "imsrg/quantum_numbers/ho_energy.h"

namespace imsrg {
class ReferenceState {
 public:
  static ReferenceState He4();
  static ReferenceState O16();

  explicit ReferenceState(const std::vector<SPState>& states);

  // Default copy, move, and dtor

  SPState GetStateWithOccupations(const SPState& state) const;

  ValidationResult ValidateAgainstEMax(HOEnergy emax) const;

  void swap(ReferenceState& other) noexcept {
    using std::swap;
    swap(ref_states_, other.ref_states_);
  }

 private:
  absl::flat_hash_map<SPStateKey, SPState> ref_states_;

  static ReferenceState FromProtonAndNeutronMax(const SPStateString& p_max,
                                                const SPStateString& n_max);
};
inline void swap(ReferenceState& a, ReferenceState& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_REFERENCE_STATE_H_
