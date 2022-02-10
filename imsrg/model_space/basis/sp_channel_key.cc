// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/sp_channel_key.h"

#include <cmath>
#include <utility>

#include "imsrg/assert.h"
#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
static std::size_t ComputeSPChannelKeyIndex(TotalAngMom jj, Parity p,
                                            IsospinProj m_tt) {
  // m_t should be -1/2 or 1/2 (nucleon)
  Expects(std::abs(m_tt.AsInt()) == 1);

  // Final 2 lines interpret even parity as 0, odd parity as 2,
  // neutron as 0, proton as 1
  // mapping p and m_tt on [0, 3]
  return 4 * static_cast<std::size_t>(jj.AsInt()) +
         2 * static_cast<std::size_t>(p.IsOdd()) +
         1 * static_cast<std::size_t>(m_tt == IsospinProj::Proton());
}
}  // namespace detail

SPChannelKey::SPChannelKey(TotalAngMom jj, Parity p, IsospinProj m_tt)
    : jj_(jj),
      p_(p),
      m_tt_(m_tt),
      index_(imsrg::detail::ComputeSPChannelKeyIndex(jj, p, m_tt)) {
  // j should be half integer
  Expects(jj_.AsInt() % 2 != 0);
  // m_t should be -1/2 or 1/2 (nucleon)
  Expects(std::abs(m_tt_.AsInt()) == 1);
}

SPChannelKey::SPChannelKey(JJ_P_M_TT jjpmtt)
    : SPChannelKey(jjpmtt.JJ(), jjpmtt.P(), jjpmtt.M_TT()) {}

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
