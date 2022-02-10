// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_PARTIAL_BASIS_H_
#define IMSRG_MODEL_SPACE_BASIS_PARTIAL_BASIS_H_

#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/model_space/basis/full_basis.h"
#include "imsrg/model_space/basis/states.h"
#include "imsrg/model_space/jj_p_m_tt.h"

namespace imsrg {

class SPPartialBasis {
 public:
  explicit SPPartialBasis(const std::vector<SPState>& states);

  // Default copy, move, and destructor

  std::size_t size() const { return states_.size(); }

  SPState at(std::size_t index) const { return states_[index]; }

  void swap(SPPartialBasis& other) noexcept {
    using std::swap;
    swap(states_, other.states_);
    swap(occs_, other.occs_);
    swap(occs_bar_, other.occs_bar_);
  }

 private:
  std::vector<SPState> states_;
  // Vector of occupations for fast access
  std::vector<double> occs_;
  // Vector of inverse occupations for fast access
  std::vector<double> occs_bar_;
  // TODO(mheinz): add lookup table for states to indices
};

inline void swap(SPPartialBasis& a, SPPartialBasis& b) noexcept { a.swap(b); }

absl::flat_hash_map<imsrg::JJ_P_M_TT, std::shared_ptr<const SPPartialBasis>>
PartitionSPFullBasisIntoSPPartialBases(const imsrg::SPFullBasis& full_basis);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_BASIS_PARTIAL_BASIS_H_
