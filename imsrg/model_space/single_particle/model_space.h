// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_
#define IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "imsrg/model_space/single_particle/channel.h"
#include "imsrg/model_space/single_particle/channel_key.h"
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

  bool IsChannelInModelSpace(SPChannelKey chankey) const {
    return defined_[chankey.Index()];
  }

  std::size_t ChannelDim(SPChannelKey chankey) const;
  const std::vector<double>& Occs(SPChannelKey chankey) const;
  const std::vector<double>& OccsBar(SPChannelKey chankey) const;

  void swap(SPModelSpace& other) noexcept {
    using std::swap;
    swap(chans_, other.chans_);
    swap(max_index_, other.max_index_);
    swap(chankeys_, other.chankeys_);
    swap(defined_, other.defined_);
    swap(dims_, other.dims_);
    swap(occs_, other.occs_);
    swap(occs_bar_, other.occs_bar_);
  }

 private:
  std::vector<SPChannel> chans_;
  std::size_t max_index_;
  std::vector<SPChannelKey> chankeys_;
  std::vector<bool> defined_;
  std::vector<std::size_t> dims_;
  std::vector<std::vector<double>> occs_;
  std::vector<std::vector<double>> occs_bar_;
};

inline void swap(SPModelSpace& a, SPModelSpace& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SINGLE_PARTICLE_MODEL_SPACE_H_
