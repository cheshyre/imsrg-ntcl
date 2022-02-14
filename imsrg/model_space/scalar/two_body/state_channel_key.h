// Copyright 2022 Matthias Heinz
#ifndef IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_KEY_H_
#define IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_KEY_H_

#include <utility>

#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
struct Scalar2BStateChannelKey {
  SPChannelKey p_chan_key;
  SPChannelKey q_chan_key;
};

template <typename H>
H AbslHashValue(H h, const Scalar2BStateChannelKey& o) {
  return H::combine(std::move(h), o.p_chan_key, o.q_chan_key);
}

void swap(Scalar2BStateChannelKey& a, Scalar2BStateChannelKey& b) noexcept;
bool operator==(const Scalar2BStateChannelKey& a,
                const Scalar2BStateChannelKey& b);

namespace detail {
imsrg::TotalAngMom MinCoupledJJ(const Scalar2BStateChannelKey& a);
imsrg::TotalAngMom MaxCoupledJJ(const Scalar2BStateChannelKey& a);
imsrg::Parity SumP(const Scalar2BStateChannelKey& a);
imsrg::Parity DiffP(const Scalar2BStateChannelKey& a);
imsrg::IsospinProj SumM_TT(const Scalar2BStateChannelKey& a);
imsrg::IsospinProj DiffM_TT(const Scalar2BStateChannelKey& a);
}  // namespace detail
}  // namespace imsrg

#endif  // IMSRG_MODEL_SPACE_SCALAR_TWO_BODY_STATE_CHANNEL_KEY_H_
