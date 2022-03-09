// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/full_basis.h"

namespace imsrg {

class SPModelSpace {
 public:
  static std::shared_ptr<const SPModelSpace> FromFullBasis(
      const SPFullBasis& full_basis);

  // Make model space from vector of *unique* channels
  explicit SPModelSpace(const std::vector<SPChannel>& chans);

  // Default copy, move, and dtor

  const std::vector<SPChannel>& Channels() const { return chans_; }

  void swap(SPModelSpace& other) noexcept {
    using std::swap;
    swap(chans_, other.chans_);
  }

 private:
  std::vector<SPChannel> chans_;
};

inline void swap(SPModelSpace& a, SPModelSpace& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_
