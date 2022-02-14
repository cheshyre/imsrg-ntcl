// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/channel_key.h"

#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/two_body/operator_channel.h"
#include "imsrg/model_space/scalar/two_body/state_channel_key.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
Scalar2BChannelKey::Scalar2BChannelKey(Scalar2BStateChannelKey bra_chan_key,
                                       Scalar2BStateChannelKey ket_chan_key,
                                       TotalAngMom jj_2b)
    : bra_chan_key_(bra_chan_key),
      ket_chan_key_(ket_chan_key),
      op_chan_(GenerateOpChannel(bra_chan_key_, ket_chan_key_, jj_2b)) {
  using imsrg::detail::MaxCoupledJJ;
  using imsrg::detail::MinCoupledJJ;
  using imsrg::detail::SumM_TT;
  using imsrg::detail::SumP;

  Expects(SumP(bra_chan_key_) == SumP(ket_chan_key_));
  Expects(SumM_TT(bra_chan_key_) == SumM_TT(ket_chan_key_));
  Expects(MinCoupledJJ(bra_chan_key_) <= jj_2b);
  Expects(MinCoupledJJ(ket_chan_key_) <= jj_2b);
  Expects(MaxCoupledJJ(bra_chan_key_) >= jj_2b);
  Expects(MaxCoupledJJ(ket_chan_key_) >= jj_2b);

  Ensures(op_chan_.P() == SumP(bra_chan_key_));
  Ensures(op_chan_.M_TT() == SumM_TT(bra_chan_key_));
  Ensures(op_chan_.JJ() == jj_2b);
}

Scalar2BOpChannel Scalar2BChannelKey::GenerateOpChannel(
    const Scalar2BStateChannelKey& bra_chan_key,
    const Scalar2BStateChannelKey& ket_chan_key, TotalAngMom jj_2b) {
  using imsrg::detail::MaxCoupledJJ;
  using imsrg::detail::MinCoupledJJ;
  using imsrg::detail::SumM_TT;
  using imsrg::detail::SumP;

  Expects(SumP(bra_chan_key) == SumP(ket_chan_key));
  Expects(SumM_TT(bra_chan_key) == SumM_TT(ket_chan_key));
  Expects(MinCoupledJJ(bra_chan_key) <= jj_2b);
  Expects(MinCoupledJJ(ket_chan_key) <= jj_2b);
  Expects(MaxCoupledJJ(bra_chan_key) >= jj_2b);
  Expects(MaxCoupledJJ(ket_chan_key) >= jj_2b);

  return Scalar2BOpChannel(jj_2b, SumP(bra_chan_key), SumM_TT(bra_chan_key));
}

bool operator==(const Scalar2BChannelKey& a, const Scalar2BChannelKey& b) {
  return ((a.BraChannelKey() == b.BraChannelKey()) &&
          (a.KetChannelKey() == b.KetChannelKey()) &&
          (a.OpChannel() == b.OpChannel()));
}
}  // namespace imsrg
