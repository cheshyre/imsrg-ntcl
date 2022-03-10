// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_ANTISYMMETRY_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_ANTISYMMETRY_H_

#include <array>

#include "imsrg/model_space/scalar/two_body/channel_key.h"

namespace imsrg {
bool IsChannelInMinimalAntisymmetricSet(const Scalar2BChannelKey& chankey);

std::array<Scalar2BChannelKey, 3> GeneratePermutedChannels(
    const Scalar2BChannelKey& chankey);

std::array<int, 3> GeneratePermutationFactors(
    const Scalar2BChannelKey& chankey);
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_ANTISYMMETRY_H_
