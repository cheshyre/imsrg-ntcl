// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/state_channel_key.h"

#include <utility>

#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
void swap(Scalar2BStateChannelKey& a, Scalar2BStateChannelKey& b) noexcept {
  using std::swap;
  swap(a.p_chan_key, b.p_chan_key);
  swap(a.q_chan_key, b.q_chan_key);
}

bool operator==(const Scalar2BStateChannelKey& a,
                const Scalar2BStateChannelKey& b) {
  return (a.p_chan_key == b.p_chan_key) && (a.q_chan_key == b.q_chan_key);
}

namespace detail {
imsrg::TotalAngMom MinCoupledJJ(const Scalar2BStateChannelKey& a) {
  return imsrg::CouplingMinimum<imsrg::TotalAngMom>(a.p_chan_key.JJ(),
                                                    a.q_chan_key.JJ());
}
imsrg::TotalAngMom MaxCoupledJJ(const Scalar2BStateChannelKey& a) {
  return imsrg::CouplingMaximum<imsrg::TotalAngMom>(a.p_chan_key.JJ(),
                                                    a.q_chan_key.JJ());
}
imsrg::Parity SumP(const Scalar2BStateChannelKey& a) {
  return a.p_chan_key.P() + a.q_chan_key.P();
}
imsrg::Parity DiffP(const Scalar2BStateChannelKey& a) {
  return a.p_chan_key.P() - a.q_chan_key.P();
}
imsrg::IsospinProj SumM_TT(const Scalar2BStateChannelKey& a) {
  return a.p_chan_key.M_TT() + a.q_chan_key.M_TT();
}
imsrg::IsospinProj DiffM_TT(const Scalar2BStateChannelKey& a) {
  return a.p_chan_key.M_TT() - a.q_chan_key.M_TT();
}
}  // namespace detail
}  // namespace imsrg
