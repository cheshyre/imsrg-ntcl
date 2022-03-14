// Copyright 2022 Matthias Heinz
#include "imsrg/files/formats/helpers/mexj.h"

#include <utility>
#include <vector>

#include "imsrg/assert.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace mexj {
NLJJTIndex::NLJJTIndex(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                       imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt)
    : index_(NLJJTIndex::ComputeIndex(n, l, jj, m_tt)) {}

std::size_t NLJJTIndex::ComputeIndex(imsrg::RadialExcitationNumber n,
                                     imsrg::OrbitalAngMom l,
                                     imsrg::TotalAngMom jj,
                                     imsrg::IsospinProj m_tt) {
  const int prev_emax = 2 * n.AsInt() + l.AsInt() - 1;
  const int prev_emax_offset = (prev_emax + 1) * (prev_emax + 2);
  // Intentional integer division
  const int offset_for_nl = (l.AsInt() / 2) * 4 - ((l.AsInt() + 1) % 2) * 2;
  const int offset_for_jj = jj.AsInt() - l.AsJJ().AsInt() + 1;
  int offset_for_m_tt = 0;
  if (m_tt == imsrg::IsospinProj::Proton()) {
    offset_for_m_tt = 1;
  }
  const int full_index =
      prev_emax_offset + offset_for_nl + offset_for_jj + offset_for_m_tt;
  Ensures(full_index >= 0);
  return static_cast<std::size_t>(full_index);
}

NLJJT::NLJJT(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
             imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt)
    : n_(n), l_(l), jj_(jj), m_tt_(m_tt), index_(n_, l_, jj_, m_tt_) {}

NLJJIndex::NLJJIndex(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                     imsrg::TotalAngMom jj)
    : index_(NLJJIndex::ComputeIndex(n, l, jj)) {}

std::size_t NLJJIndex::ComputeIndex(imsrg::RadialExcitationNumber n,
                                    imsrg::OrbitalAngMom l,
                                    imsrg::TotalAngMom jj) {
  const int prev_emax = 2 * n.AsInt() + l.AsInt() - 1;
  const int prev_emax_offset = (prev_emax + 1) * (prev_emax + 2);
  // Intentional integer division
  const int offset_for_nl = (l.AsInt() / 2) * 4 - ((l.AsInt() + 1) % 2) * 2;
  const int offset_for_jj = jj.AsInt() - l.AsJJ().AsInt() + 1;
  const int full_index = prev_emax_offset + offset_for_nl + offset_for_jj;
  Ensures(full_index >= 0);
  Ensures(full_index % 2 == 0);
  return static_cast<std::size_t>(full_index / 2);
}

NLJJ::NLJJ(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
           imsrg::TotalAngMom jj)
    : n_(n), l_(l), jj_(jj), index_(n_, l_, jj_) {}

std::vector<NLJJT> GetNLJJTs(imsrg::HOEnergy emax) {
  const std::vector<imsrg::IsospinProj> m_tts = {imsrg::IsospinProj::Neutron(),
                                                 imsrg::IsospinProj::Proton()};

  std::vector<NLJJT> nljjts;

  for (int e = 0; e <= emax.AsInt(); e += 1) {
    for (int l = e % 2; l <= e; l += 2) {
      int n = (e - l) / 2;
      std::vector<int> jjvals;
      if (l != 0) {
        jjvals.push_back(2 * l - 1);
      }
      jjvals.push_back(2 * l + 1);
      for (const auto& jj : jjvals) {
        for (const auto& m_tt : m_tts) {
          nljjts.push_back(NLJJT(imsrg::RadialExcitationNumber(n),
                                 imsrg::OrbitalAngMom(l),
                                 imsrg::TotalAngMom(jj), m_tt));
        }
      }
    }
  }
  return nljjts;
}
std::vector<NLJJ> GetNLJJs(imsrg::HOEnergy emax) {
  std::vector<NLJJ> nljjs;

  for (int e = 0; e <= emax.AsInt(); e += 1) {
    for (int l = e % 2; l <= e; l += 2) {
      int n = (e - l) / 2;
      std::vector<int> jjvals;
      if (l != 0) {
        jjvals.push_back(2 * l - 1);
      }
      jjvals.push_back(2 * l + 1);
      for (const auto& jj : jjvals) {
        nljjs.push_back(NLJJ(imsrg::RadialExcitationNumber(n),
                             imsrg::OrbitalAngMom(l), imsrg::TotalAngMom(jj)));
      }
    }
  }
  return nljjs;
}

NLJJTIndex2::NLJJTIndex2(NLJJTIndex i1, NLJJTIndex i2)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor) {}
NLJJTIndex3::NLJJTIndex3(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2) {}
NLJJTIndex4::NLJJTIndex4(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                         NLJJTIndex i4)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3) {}
NLJJTIndex5::NLJJTIndex5(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                         NLJJTIndex i4, NLJJTIndex i5)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3 +
             i5.AsSizeT() * kMEXJIndexFoldFactor4) {}
NLJJTIndex6::NLJJTIndex6(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                         NLJJTIndex i4, NLJJTIndex i5, NLJJTIndex i6)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3 +
             i5.AsSizeT() * kMEXJIndexFoldFactor4 +
             i6.AsSizeT() * kMEXJIndexFoldFactor5) {}

NLJJIndex2::NLJJIndex2(NLJJIndex i1, NLJJIndex i2)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor) {}
NLJJIndex3::NLJJIndex3(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2) {}
NLJJIndex4::NLJJIndex4(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3) {}
NLJJIndex5::NLJJIndex5(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4,
                       NLJJIndex i5)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3 +
             i5.AsSizeT() * kMEXJIndexFoldFactor4) {}
NLJJIndex6::NLJJIndex6(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4,
                       NLJJIndex i5, NLJJIndex i6)
    : index_(i1.AsSizeT() + i2.AsSizeT() * kMEXJIndexFoldFactor +
             i3.AsSizeT() * kMEXJIndexFoldFactor2 +
             i4.AsSizeT() * kMEXJIndexFoldFactor3 +
             i5.AsSizeT() * kMEXJIndexFoldFactor4 +
             i6.AsSizeT() * kMEXJIndexFoldFactor5) {}

}  // namespace mexj

}  // namespace imsrg
