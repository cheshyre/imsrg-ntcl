// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_BARE_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_BARE_CHANNEL_KEY_H_

#include <utility>

#include "imsrg/model_space/single_particle/channel_key.h"

namespace imsrg {
struct Scalar2BBareChannelKey {
  SPChannelKey chankey_1;
  SPChannelKey chankey_2;
  SPChannelKey chankey_3;
  SPChannelKey chankey_4;
};

inline void swap(Scalar2BBareChannelKey& a,
                 Scalar2BBareChannelKey& b) noexcept {
  using std::swap;
  swap(a.chankey_1, b.chankey_1);
  swap(a.chankey_2, b.chankey_2);
  swap(a.chankey_3, b.chankey_3);
  swap(a.chankey_4, b.chankey_4);
}

bool operator==(const Scalar2BBareChannelKey& a,
                const Scalar2BBareChannelKey& b);

inline bool operator!=(const Scalar2BBareChannelKey& a,
                       const Scalar2BBareChannelKey& b) {
  return !(a == b);
}

}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_BARE_CHANNEL_KEY_H_
