// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/two_body/read.h"

#include "imsrg/assert.h"
#include "imsrg/files/formats/me2jp.h"
#include "imsrg/operator/scalar/two_body/operator.h"

namespace imsrg {

void ReadOperatorFromME2JP(const ME2JPFile& me2jp, Scalar2BOperator& op) {
  Expects(me2jp.Herm() == op.Herm());

  const auto& ms = op.GetModelSpace();

  for (std::size_t index = 0; index < ms.NumberOfChannels(); index += 1) {
    auto& tensor_mut = op.GetMutableTensorAtIndex(index);
    const auto& channel = ms.ChannelAtIndex(index);

    const auto jj = channel.ChannelKey().OpChannel().JJ();

    const auto& chan_p = channel.BraChannel1();
    const auto& chan_q = channel.BraChannel2();
    const auto& chan_r = channel.KetChannel1();
    const auto& chan_s = channel.KetChannel2();

    const auto& basis_p = chan_p.ChannelBasis();
    const auto& basis_q = chan_q.ChannelBasis();
    const auto& basis_r = chan_r.ChannelBasis();
    const auto& basis_s = chan_s.ChannelBasis();

    for (std::size_t s_i = 0; s_i < basis_s.size(); s_i += 1) {
      const auto s = basis_s.at(s_i);
      for (std::size_t r_i = 0; r_i < basis_r.size(); r_i += 1) {
        const auto r = basis_r.at(r_i);
        for (std::size_t q_i = 0; q_i < basis_q.size(); q_i += 1) {
          const auto q = basis_q.at(q_i);
          for (std::size_t p_i = 0; p_i < basis_p.size(); p_i += 1) {
            const auto p = basis_p.at(p_i);
            tensor_mut(p_i, q_i, r_i, s_i) =
                me2jp.Get2BMatrixElement(p, q, r, s, jj);
          }
        }
      }
    }
  }
}

}  // namespace imsrg
