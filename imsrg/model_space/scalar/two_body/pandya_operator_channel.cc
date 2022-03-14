// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/pandya_operator_channel.h"

#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
namespace detail {
static std::uint16_t GeneratePackedRepresentation(imsrg::TotalAngMom jj,
                                                  imsrg::Parity p,
                                                  imsrg::IsospinProj m_ttau);
}

Scalar2BPandyaOpChannel::Scalar2BPandyaOpChannel(TotalAngMom jj, Parity p,
                                                 IsospinProj m_ttau)
    : packed_rep_(imsrg::detail::GeneratePackedRepresentation(jj, p, m_ttau)) {}

// Default copy, move, dtor

imsrg::TotalAngMom Scalar2BPandyaOpChannel::JJ() const {
  return imsrg::TotalAngMom((packed_rep_ >> 3) * 2);
}

imsrg::Parity Scalar2BPandyaOpChannel::P() const {
  const std::int16_t mask = 1;
  if (static_cast<bool>(packed_rep_ & mask)) {
    return imsrg::Parity::Odd();
  }
  return imsrg::Parity::Even();
}

imsrg::IsospinProj Scalar2BPandyaOpChannel::M_TTau() const {
  const std::int16_t mask = 3;
  return imsrg::IsospinProj(static_cast<int>((packed_rep_ >> 1) & mask) * 2 -
                            2);
}

namespace detail {
static std::uint16_t GeneratePackedRepresentation(imsrg::TotalAngMom jj,
                                                  imsrg::Parity p,
                                                  imsrg::IsospinProj m_ttau) {
  Expects(jj.IsInteger());
  Expects(m_ttau.IsInteger() && (m_ttau.AsInt() <= 2) &&
          (m_ttau.AsInt() >= -2));

  std::uint16_t jj_index = static_cast<std::uint16_t>(jj.AsInt()) / 2;
  std::uint16_t m_ttau_index =
      static_cast<std::uint16_t>(m_ttau.AsInt() + 2) / 2;
  std::uint16_t p_index = static_cast<std::uint16_t>(p.IsOdd());

  return (jj_index << 3) + (m_ttau_index << 1) + (p_index);
}
}  // namespace detail
}  // namespace imsrg
