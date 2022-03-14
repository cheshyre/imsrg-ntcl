// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/one_body/read.h"

#include "imsrg/assert.h"
#include "imsrg/files/formats/me1j.h"
#include "imsrg/operator/scalar/one_body/operator.h"

namespace imsrg {

void ReadOperatorFromME1J(const ME1JFile& me1j, Scalar1BOperator& op) {
  Expects(me1j.Herm() == op.Herm());

  const auto& ms = op.GetModelSpace();

  for (std::size_t index = 0; index < ms.NumberOfChannels(); index += 1) {
    auto& tensor_mut = op.GetMutableTensorAtIndex(index);
    const auto& channel = ms.ChannelAtIndex(index);

    const auto& chan_bra = channel.BraChannel();
    const auto& chan_ket = channel.KetChannel();

    const auto& basis_bra = chan_bra.ChannelBasis();
    const auto& basis_ket = chan_ket.ChannelBasis();

    for (std::size_t p_i = 0; p_i < basis_bra.size(); p_i += 1) {
      const auto p = basis_bra.at(p_i);
      for (std::size_t q_i = 0; q_i < basis_ket.size(); q_i += 1) {
        const auto q = basis_bra.at(q_i);
        tensor_mut(p_i, q_i) = me1j.Get1BMatrixElement(p, q);
      }
    }
  }
}

}  // namespace imsrg
