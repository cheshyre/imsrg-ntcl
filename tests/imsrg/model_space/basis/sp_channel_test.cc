// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/sp_channel.h"

#include <memory>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "fmt/core.h"

#include "imsrg/model_space/basis/sp_channel_key.h"
#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

static std::vector<imsrg::TotalAngMom> ValidJJs() {
  return {
      imsrg::TotalAngMom(1),  imsrg::TotalAngMom(3),  imsrg::TotalAngMom(5),
      imsrg::TotalAngMom(7),  imsrg::TotalAngMom(9),  imsrg::TotalAngMom(11),
      imsrg::TotalAngMom(13), imsrg::TotalAngMom(15), imsrg::TotalAngMom(17),
      imsrg::TotalAngMom(19), imsrg::TotalAngMom(21)};
}

static std::vector<imsrg::IsospinProj> ValidM_TTs() {
  return {imsrg::IsospinProj::Neutron(), imsrg::IsospinProj::Proton()};
}

static std::vector<imsrg::Parity> ValidPs() {
  return {imsrg::Parity::Even(), imsrg::Parity::Odd()};
}

static std::vector<imsrg::JJ_P_M_TT> ValidJJPMTTs() {
  std::vector<imsrg::JJ_P_M_TT> valid;
  for (const auto jj : ValidJJs()) {
    for (const auto p : ValidPs()) {
      for (const auto m_tt : ValidM_TTs()) {
        valid.push_back(imsrg::JJ_P_M_TT(jj, p, m_tt));
      }
    }
  }
  return valid;
}

static absl::flat_hash_map<imsrg::SPChannelKey,
                           std::shared_ptr<const imsrg::SPPartialBasis>>
CreateEMax2Partitioning() {
  using imsrg::HOEnergy;
  using imsrg::IsospinProj;
  using imsrg::OrbitalAngMom;
  using imsrg::Parity;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPChannelKey;
  using imsrg::SPPartialBasis;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  HOEnergy emax(2);

  absl::flat_hash_map<SPChannelKey, std::shared_ptr<const SPPartialBasis>>
      partitioning;

  for (const auto jjpmtt : ValidJJPMTTs()) {
    const auto jj = jjpmtt.JJ();
    const auto m_tt = jjpmtt.M_TT();
    OrbitalAngMom l((jj.AsInt() + 1) / 2);
    if (l.Parity() != jjpmtt.P()) {
      l = OrbitalAngMom((jj.AsInt() - 1) / 2);
    }

    std::vector<SPState> states;
    for (int n_i = 0; n_i <= emax.AsInt() / 2; n_i++) {
      RadialExcitationNumber n(n_i);

      SPState cand_state(n, l, jj, m_tt);

      if (cand_state.E() <= emax) {
        states.push_back(cand_state);
      } else {
        break;
      }
    }
    partitioning[SPChannelKey(jjpmtt)] =
        std::make_shared<const SPPartialBasis>(states);
  }
  return partitioning;
}

static absl::flat_hash_map<imsrg::SPChannelKey,
                           std::shared_ptr<const imsrg::SPPartialBasis>>&
GetEMax2Partitioning() {
  static absl::flat_hash_map<imsrg::SPChannelKey,
                             std::shared_ptr<const imsrg::SPPartialBasis>>
      partitioning(CreateEMax2Partitioning());
  return partitioning;
}

static std::shared_ptr<const imsrg::SPPartialBasis> GetPartialBasisPtr(
    imsrg::SPChannelKey key) {
  auto& partitioning = GetEMax2Partitioning();

  if (partitioning.find(key) == partitioning.end()) {
    partitioning[key] = std::make_shared<const imsrg::SPPartialBasis>(
        std::vector<imsrg::SPState>());
  }

  return partitioning[key];
}

TEST_CASE("Test ctor and JJ(), P(), M_TT().") {
  for (const auto jjpmtt : ValidJJPMTTs()) {
    imsrg::SPChannelKey chankey(jjpmtt);
    auto basis_ptr = GetPartialBasisPtr(chankey);
    imsrg::SPChannel chan(chankey, basis_ptr);
    REQUIRE(chan.JJ() == jjpmtt.JJ());
    REQUIRE(chan.P() == jjpmtt.P());
    REQUIRE(chan.M_TT() == jjpmtt.M_TT());
  }
}

TEST_CASE("Test sizes (emax=2).") {
  using imsrg::TotalAngMom;

  for (const auto jjpmtt : ValidJJPMTTs()) {
    imsrg::SPChannelKey chankey(jjpmtt);
    auto basis_ptr = GetPartialBasisPtr(chankey);
    imsrg::SPChannel chan(chankey, basis_ptr);
    if ((jjpmtt.JJ() == TotalAngMom(1)) && jjpmtt.P().IsEven()) {
      // s1/2
      REQUIRE(chan.size() == 2);
    } else if ((jjpmtt.JJ() == TotalAngMom(1)) && jjpmtt.P().IsOdd()) {
      // p1/2
      REQUIRE(chan.size() == 1);
    } else if ((jjpmtt.JJ() == TotalAngMom(3)) && jjpmtt.P().IsOdd()) {
      // p3/2
      REQUIRE(chan.size() == 1);
    } else if ((jjpmtt.JJ() == TotalAngMom(3)) && jjpmtt.P().IsEven()) {
      // d3/2
      REQUIRE(chan.size() == 1);
    } else if ((jjpmtt.JJ() == TotalAngMom(5)) && jjpmtt.P().IsEven()) {
      // d5/2
      REQUIRE(chan.size() == 1);
    } else {
      // rest
      REQUIRE(chan.size() == 0);
    }
  }
}

TEST_CASE("Test index.") {
  using imsrg::TotalAngMom;

  for (const auto jjpmtt : ValidJJPMTTs()) {
    imsrg::SPChannelKey chankey(jjpmtt);
    auto basis_ptr = GetPartialBasisPtr(chankey);
    imsrg::SPChannel chan(chankey, basis_ptr);
    REQUIRE(chan.Index() == chankey.Index());
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::SPChannel>::value);
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::SPChannel>::value);
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::SPChannel>::value);
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::SPChannel>::value);
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::SPChannel>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::SPChannel>::value);

  for (const auto jjpmtt1 : ValidJJPMTTs()) {
    for (const auto jjpmtt2 : ValidJJPMTTs()) {
      imsrg::SPChannelKey chankey1(jjpmtt1);
      imsrg::SPChannel chan1(chankey1, GetPartialBasisPtr(chankey1));
      imsrg::SPChannelKey chankey2(jjpmtt2);
      imsrg::SPChannel chan2(chankey2, GetPartialBasisPtr(chankey2));

      // Save results
      auto jj1 = chan1.JJ();
      auto p1 = chan1.P();
      auto m_tt1 = chan1.M_TT();
      auto index1 = chan1.Index();
      auto size1 = chan1.size();
      auto jj2 = chan2.JJ();
      auto p2 = chan2.P();
      auto m_tt2 = chan2.M_TT();
      auto index2 = chan2.Index();
      auto size2 = chan2.size();

      chan1.swap(chan2);

      REQUIRE(chan1.JJ() == jj2);
      REQUIRE(chan1.P() == p2);
      REQUIRE(chan1.M_TT() == m_tt2);
      REQUIRE(chan1.Index() == index2);
      REQUIRE(chan1.size() == size2);
      REQUIRE(chan2.JJ() == jj1);
      REQUIRE(chan2.P() == p1);
      REQUIRE(chan2.M_TT() == m_tt1);
      REQUIRE(chan2.Index() == index1);
      REQUIRE(chan2.size() == size1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPChannel>::value);

  for (const auto jjpmtt1 : ValidJJPMTTs()) {
    for (const auto jjpmtt2 : ValidJJPMTTs()) {
      imsrg::SPChannelKey chankey1(jjpmtt1);
      imsrg::SPChannel chan1(chankey1, GetPartialBasisPtr(chankey1));
      imsrg::SPChannelKey chankey2(jjpmtt2);
      imsrg::SPChannel chan2(chankey2, GetPartialBasisPtr(chankey2));

      // Save results
      auto jj1 = chan1.JJ();
      auto p1 = chan1.P();
      auto m_tt1 = chan1.M_TT();
      auto index1 = chan1.Index();
      auto size1 = chan1.size();
      auto jj2 = chan2.JJ();
      auto p2 = chan2.P();
      auto m_tt2 = chan2.M_TT();
      auto index2 = chan2.Index();
      auto size2 = chan2.size();

      swap(chan1, chan2);

      REQUIRE(chan1.JJ() == jj2);
      REQUIRE(chan1.P() == p2);
      REQUIRE(chan1.M_TT() == m_tt2);
      REQUIRE(chan1.Index() == index2);
      REQUIRE(chan1.size() == size2);
      REQUIRE(chan2.JJ() == jj1);
      REQUIRE(chan2.P() == p1);
      REQUIRE(chan2.M_TT() == m_tt1);
      REQUIRE(chan2.Index() == index1);
      REQUIRE(chan2.size() == size1);
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto jjpmtt1 : ValidJJPMTTs()) {
    const imsrg::SPChannelKey chankey1(jjpmtt1);
    const imsrg::SPChannel chan1(chankey1, GetPartialBasisPtr(chankey1));
    for (const auto jjpmtt2 : ValidJJPMTTs()) {
      const imsrg::SPChannelKey chankey2(jjpmtt2);
      const imsrg::SPChannel chan2(chankey2, GetPartialBasisPtr(chankey2));

      REQUIRE((chan1 == chan2) == (chankey1 == chankey2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto jjpmtt1 : ValidJJPMTTs()) {
    const imsrg::SPChannelKey chankey1(jjpmtt1);
    const imsrg::SPChannel chan1(chankey1, GetPartialBasisPtr(chankey1));
    for (const auto jjpmtt2 : ValidJJPMTTs()) {
      const imsrg::SPChannelKey chankey2(jjpmtt2);
      const imsrg::SPChannel chan2(chankey2, GetPartialBasisPtr(chankey2));

      REQUIRE((chan1 != chan2) == (chankey1 != chankey2));
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto jjpmtt1 : ValidJJPMTTs()) {
    const imsrg::SPChannelKey chankey1(jjpmtt1);
    const imsrg::SPChannel chan1(chankey1, GetPartialBasisPtr(chankey1));
    for (const auto jjpmtt2 : ValidJJPMTTs()) {
      const imsrg::SPChannelKey chankey2(jjpmtt2);
      const imsrg::SPChannel chan2(chankey2, GetPartialBasisPtr(chankey2));

      REQUIRE((chan1 < chan2) == (chan1.Index() < chan2.Index()));
    }
  }
}
