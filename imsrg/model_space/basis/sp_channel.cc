// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/sp_channel.h"

#include <memory>
#include <utility>

#include "imsrg/model_space/basis/partial_basis.h"
#include "imsrg/model_space/basis/sp_channel_key.h"

namespace imsrg {
SPChannel::SPChannel(SPChannelKey chan_key,
                     std::shared_ptr<const SPPartialBasis> basis_ptr)
    : chan_key_(chan_key), basis_ptr_(basis_ptr), size_(basis_ptr_->size()) {
  // TODO(mheinz) add a nullptr check
  // Expects(all states in partial basis to have same JJ, P, and T as
  // chan_key)
}

void SPChannel::swap(SPChannel& other) noexcept {
  using std::swap;
  swap(chan_key_, other.chan_key_);
  swap(basis_ptr_, other.basis_ptr_);
  swap(size_, other.size_);
}

bool operator==(const SPChannel& a, const SPChannel& b) {
  return a.Index() == b.Index();
}

bool operator!=(const SPChannel& a, const SPChannel& b) {
  return a.Index() != b.Index();
}

bool operator<(const SPChannel& a, const SPChannel& b) {
  return a.Index() < b.Index();
}

}  // namespace imsrg
