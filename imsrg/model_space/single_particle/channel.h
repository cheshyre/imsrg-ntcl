// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_H_

#include <memory>
#include <utility>

#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/model_space/single_particle/partial_basis.h"

namespace imsrg {

class SPChannel {
 public:
  explicit SPChannel(SPChannelKey chan_key,
                     std::shared_ptr<const SPPartialBasis> basis_ptr);

  TotalAngMom JJ() const { return chan_key_.JJ(); }
  Parity P() const { return chan_key_.P(); }
  IsospinProj M_TT() const { return chan_key_.M_TT(); }
  std::size_t Index() const { return chan_key_.Index(); }

  SPChannelKey ChannelKey() const { return chan_key_; }

  const SPPartialBasis& ChannelBasis() const { return *basis_ptr_; }

  // Get size of basis
  std::size_t size() const { return size_; }

  void swap(SPChannel& other) noexcept {
    using std::swap;
    swap(chan_key_, other.chan_key_);
    swap(basis_ptr_, other.basis_ptr_);
    swap(size_, other.size_);
  }

 private:
  SPChannelKey chan_key_;
  std::shared_ptr<const SPPartialBasis> basis_ptr_;
  std::size_t size_;
};

inline void swap(SPChannel& a, SPChannel& b) noexcept { a.swap(b); }

bool operator==(const SPChannel& a, const SPChannel& b);

bool operator!=(const SPChannel& a, const SPChannel& b);

// Defined for sorting purposes
bool operator<(const SPChannel& a, const SPChannel& b);

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_CHANNEL_H_
