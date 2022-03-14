// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_MODEL_SPACE_H_
#define IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_MODEL_SPACE_H_

#include <memory>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/model_space/scalar/one_body/channel.h"
#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/model_space/single_particle/model_space.h"

namespace imsrg {
class Scalar1BModelSpace {
 public:
  static std::shared_ptr<const Scalar1BModelSpace> FromSPModelSpace(
      const std::shared_ptr<const SPModelSpace>& sp_ms);

  // Ctor from a vector of channels
  // YOU SHOULD NOT CALL THIS DIRECTLY.
  explicit Scalar1BModelSpace(std::vector<Scalar1BChannel>&& chans);

  // Not copyable or movable (only pointers)
  Scalar1BModelSpace(const Scalar1BModelSpace&) = delete;
  Scalar1BModelSpace& operator=(const Scalar1BModelSpace&) = delete;
  Scalar1BModelSpace(Scalar1BModelSpace&&) = delete;
  Scalar1BModelSpace& operator=(Scalar1BModelSpace&&) = delete;

  // Default dtor

  std::size_t size() const { return chans_.size(); }
  std::size_t NumberOfChannels() const { return size(); }

  const Scalar1BChannel& ChannelAtIndex(std::size_t index) const {
    return chans_[index];
  }

  bool IsChannelInModelSpace(Scalar1BChannelKey chankey) const;
  std::size_t IndexOfChannelInModelSpace(Scalar1BChannelKey chankey) const;

  void swap(Scalar1BModelSpace& other) noexcept {
    using std::swap;
    swap(chans_, other.chans_);
    swap(chan_index_lookup_, other.chan_index_lookup_);
  }

 private:
  std::vector<Scalar1BChannel> chans_;
  absl::flat_hash_map<Scalar1BChannelKey, std::size_t> chan_index_lookup_;
};

inline void swap(Scalar1BModelSpace& a, Scalar1BModelSpace& b) noexcept {
  a.swap(b);
}
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_ONE_BODY_MODEL_SPACE_H_
