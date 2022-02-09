// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_H_
#define IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_H_

#include <memory>
#include <utility>

#include "imsrg/model_space/basis/partial_basis.h"
#include "imsrg/model_space/basis/sp_channel_key.h"

namespace imsrg {

class SPChannel {
 private:
  SPChannelKey chan_key_;
  std::shared_ptr<const SPPartialBasis> basis_ptr_;
  std::size_t size_;

 public:
  explicit SPChannel(SPChannelKey chan_key,
                     std::shared_ptr<const SPPartialBasis> basis_ptr)
      : chan_key_(chan_key), basis_ptr_(basis_ptr), size_(basis_ptr_->size()) {
    // TODO(mheinz) add a nullptr check
    // Expects(all states in partial basis to have same JJ, P, and T as
    // chan_key)
  }

  TotalAngMom JJ() const { return chan_key_.JJ(); }
  Parity P() const { return chan_key_.P(); }
  IsospinProj M_TT() const { return chan_key_.M_TT(); }
  std::size_t Index() const { return chan_key_.Index(); }

  // Get size of basis
  std::size_t size() const { return size_; }

  void swap(SPChannel& other) noexcept {
    using std::swap;
    swap(chan_key_, other.chan_key_);
    swap(basis_ptr_, other.basis_ptr_);
    swap(size_, other.size_);
  }
};

inline void swap(SPChannel& a, SPChannel& b) noexcept { a.swap(b); }

inline bool operator==(const SPChannel& a, const SPChannel& b) {
  return a.Index() == b.Index();
}

inline bool operator!=(const SPChannel& a, const SPChannel& b) {
  return a.Index() != b.Index();
}

// Defined for sorting purposes
inline bool operator<(const SPChannel& a, const SPChannel& b) {
  return a.Index() < b.Index();
}

}  // namespace imsrg

#endif  //  IMSRG_MODEL_SPACE_BASIS_SP_CHANNEL_H_
