// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/reference_state.h"

#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "fmt/core.h"

#include "imsrg/error.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/model_space/single_particle/state_key.h"
#include "imsrg/model_space/single_particle/state_string.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/occupation_number.h"

namespace imsrg {

namespace detail {
absl::flat_hash_map<SPStateKey, SPState> GenerateLookup(
    const std::vector<SPState>& states);
}

ReferenceState ReferenceState::He4() {
  return ReferenceState::FromProtonAndNeutronMax(SPStateString("p0s1/2"),
                                                 SPStateString("n0s1/2"));
}

ReferenceState ReferenceState::O16() {
  return ReferenceState::FromProtonAndNeutronMax(SPStateString("p0p1/2"),
                                                 SPStateString("n0p1/2"));
}

ReferenceState::ReferenceState(const std::vector<SPState>& states)
    : ref_states_(imsrg::detail::GenerateLookup(states)) {}

// Default copy, move, and dtor

SPState ReferenceState::GetStateWithOccupations(const SPState& state) const {
  const auto search = ref_states_.find(state.StateKey());
  if (search == ref_states_.end()) {
    return state;
  }
  return search->second;
}

ValidationResult ReferenceState::ValidateAgainstEMax(HOEnergy emax) const {
  for (const auto& it : ref_states_) {
    if (it.second.E() > emax) {
      return {false,
              fmt::format("{} state in reference state with occupation "
                          "{} is outside of emax={} truncation.",
                          it.second.StateString().String(),
                          it.second.OccupationN().AsDouble(), emax.AsInt())};
    }
  }
  return {true};
}

ReferenceState ReferenceState::FromProtonAndNeutronMax(
    const SPStateString& p_max, const SPStateString& n_max) {
  auto p_states = SPStateString::GetProtonOrbitalsUpToMax(p_max);
  auto n_states = SPStateString::GetNeutronOrbitalsUpToMax(n_max);

  std::vector<SPState> ref_states;
  ref_states.reserve(p_states.size() + n_states.size());

  for (const auto& x : p_states) {
    ref_states.push_back(SPState(x, OccupationNumber(1.0)));
  }

  for (const auto& x : n_states) {
    ref_states.push_back(SPState(x, OccupationNumber(1.0)));
  }

  return ReferenceState(ref_states);
}

namespace detail {
absl::flat_hash_map<imsrg::SPStateKey, imsrg::SPState> GenerateLookup(
    const std::vector<imsrg::SPState>& states) {
  absl::flat_hash_map<imsrg::SPStateKey, imsrg::SPState> lookup;
  lookup.reserve(states.size());
  for (const auto& s : states) {
    lookup.emplace(s.StateKey(), s);
  }
  return lookup;
}
}  // namespace detail

}  // namespace imsrg
