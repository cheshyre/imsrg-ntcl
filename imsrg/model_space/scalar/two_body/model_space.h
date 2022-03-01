// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_MODEL_SPACE_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_MODEL_SPACE_H_

#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/model_space/scalar/two_body/channel.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/single_particle/model_space.h"

namespace imsrg {

class Scalar2BModelSpace {
 public:
  static std::shared_ptr<const Scalar2BModelSpace> FromSPModelSpace(
      const SPModelSpace& sp_ms);

  // Ctor from a vector of channels
  // YOU SHOULD NOT CALL THIS DIRECTLY.
  explicit Scalar2BModelSpace(std::vector<Scalar2BChannel>&& chans);

  // Not copyable or movable (only pointers)
  Scalar2BModelSpace(const Scalar2BModelSpace&) = delete;
  Scalar2BModelSpace& operator=(const Scalar2BModelSpace&) = delete;
  Scalar2BModelSpace(Scalar2BModelSpace&&) = delete;
  Scalar2BModelSpace& operator=(Scalar2BModelSpace&&) = delete;

  // Default dtor

  std::size_t size() const { return chans_.size(); }
  std::size_t NumberOfChannels() const { return size(); }

  const Scalar2BChannel& ChannelAtIndex(std::size_t index) const {
    return chans_[index];
  }

  bool IsChannelInModelSpace(Scalar2BChannelKey chankey) const;
  std::size_t IndexOfChannelInModelSpace(Scalar2BChannelKey chankey) const;

  void swap(Scalar2BModelSpace& other) noexcept {
    using std::swap;
    swap(chans_, other.chans_);
    swap(chan_index_lookup_, other.chan_index_lookup_);
  }

 private:
  std::vector<Scalar2BChannel> chans_;
  absl::flat_hash_map<Scalar2BChannelKey, std::size_t> chan_index_lookup_;
};

inline void swap(Scalar2BModelSpace& a, Scalar2BModelSpace& b) noexcept {
  a.swap(b);
}
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_MODEL_SPACE_H_
