// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/channel_key.h"

#include <cmath>
#include <cstdint>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
static std::uint8_t ComputeSPChannelKeyIndex(TotalAngMom jj, Parity p,
                                             IsospinProj m_tt) {
  // m_t should be -1/2 or 1/2 (nucleon)
  Expects((m_tt == IsospinProj::Neutron()) || (m_tt == IsospinProj::Proton()));
  Expects(jj.IsHalfInteger());

  // Final 2 lines interpret even parity as 0, odd parity as 2,
  // neutron as 0, proton as 1
  // mapping p and m_tt on [0, 3]
  return 4 * static_cast<std::uint8_t>((jj.AsInt() - 1) / 2) +
         2 * static_cast<std::uint8_t>(p.IsOdd()) +
         1 * static_cast<std::uint8_t>(m_tt == IsospinProj::Proton());
}
}  // namespace detail

SPChannelKey::SPChannelKey(TotalAngMom jj, Parity p, IsospinProj m_tt)
    : packed_rep_(imsrg::detail::ComputeSPChannelKeyIndex(jj, p, m_tt)) {}

SPChannelKey::SPChannelKey(JJ_P_M_TT jjpmtt)
    : SPChannelKey(jjpmtt.JJ(), jjpmtt.P(), jjpmtt.M_TT()) {}

TotalAngMom SPChannelKey::JJ() const {
  return TotalAngMom(static_cast<int>((packed_rep_ & 252) >> 2) * 2 + 1);
}
Parity SPChannelKey::P() const {
  if (packed_rep_ & 2) {
    return Parity::Odd();
  }
  return Parity::Even();
}
IsospinProj SPChannelKey::M_TT() const {
  if (packed_rep_ & 1) {
    return IsospinProj::Proton();
  }
  return IsospinProj::Neutron();
}

bool operator==(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() == b.Index();
}

bool operator!=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() != b.Index();
}

bool operator<(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() < b.Index();
}

bool operator<=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() <= b.Index();
}

bool operator>(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() > b.Index();
}

bool operator>=(const SPChannelKey& a, const SPChannelKey& b) {
  return a.Index() >= b.Index();
}

}  // namespace imsrg
