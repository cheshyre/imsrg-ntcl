// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/partial_basis.h"

#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"

namespace imsrg {
namespace detail {
static std::vector<double> ExtractOccsFromStatesVector(
    const std::vector<SPState>& states);
static std::vector<double> ExtractOccsBarFromStatesVector(
    const std::vector<SPState>& states);
}  // namespace detail

SPPartialBasis::SPPartialBasis(const std::vector<SPState>& states)
    : states_(states),
      occs_(imsrg::detail::ExtractOccsFromStatesVector(states)),
      occs_bar_(imsrg::detail::ExtractOccsBarFromStatesVector(states)) {}

absl::flat_hash_map<imsrg::JJ_P_M_TT, std::shared_ptr<const SPPartialBasis>>
PartitionSPFullBasisIntoSPPartialBases(const imsrg::SPFullBasis& full_basis) {
  absl::flat_hash_set<imsrg::JJ_P_M_TT> jjpmtts;

  for (std::size_t index = 0; index < full_basis.size(); index++) {
    jjpmtts.insert(full_basis.at(index).GetJJ_P_M_TT());
  }

  absl::flat_hash_map<imsrg::JJ_P_M_TT, std::shared_ptr<const SPPartialBasis>>
      lookup;
  for (const auto jjpmtt : jjpmtts) {
    std::vector<SPState> partial_basis;

    for (std::size_t index = 0; index < full_basis.size(); index++) {
      if (full_basis.at(index).GetJJ_P_M_TT() == jjpmtt) {
        partial_basis.push_back(full_basis.at(index));
      }
    }

    lookup.emplace(jjpmtt,
                   std::make_shared<const SPPartialBasis>(partial_basis));
  }

  return lookup;
}

namespace detail {
static std::vector<double> ExtractOccsFromStatesVector(
    const std::vector<SPState>& states) {
  std::vector<double> occs;
  occs.reserve(states.size());

  for (const auto& x : states) {
    occs.push_back(x.OccupationN().AsDouble());
  }
  return occs;
}
static std::vector<double> ExtractOccsBarFromStatesVector(
    const std::vector<SPState>& states) {
  std::vector<double> occsbar;
  occsbar.reserve(states.size());

  for (const auto& x : states) {
    occsbar.push_back(x.OccupationN().NBarAsDouble());
  }
  return occsbar;
}
}  // namespace detail
}  // namespace imsrg
