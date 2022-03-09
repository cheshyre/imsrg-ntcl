// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/bare_channel_key.h"

#include <utility>

#include "imsrg/model_space/single_particle/channel_key.h"

namespace imsrg {

bool operator==(const Scalar2BBareChannelKey& a,
                const Scalar2BBareChannelKey& b) {
  return (a.chankey_1 == b.chankey_1) && (a.chankey_2 == b.chankey_2) &&
         (a.chankey_3 == b.chankey_3) && (a.chankey_4 == b.chankey_4);
}

}  // namespace imsrg
