// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/basis/sp_model_space.h"

#include <memory>
#include <vector>

#include "imsrg/model_space/basis/sp_channel.h"
#include "imsrg/model_space/basis/sp_channel_key.h"
#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/helpers/equality.h"

#include "tests/catch.hpp"

static std::vector<imsrg::TotalAngMom> ValidJJs(imsrg::TotalAngMom jjmax) {
  std::vector<imsrg::TotalAngMom> valid;
  for (int jj_i = 1; jj_i <= jjmax.AsInt(); jj_i += 2) {
    valid.push_back(imsrg::TotalAngMom(jj_i));
  }
  return valid;
}

static std::vector<imsrg::IsospinProj> ValidM_TTs() {
  return {imsrg::IsospinProj::Neutron(), imsrg::IsospinProj::Proton()};
}

static std::vector<imsrg::Parity> ValidPs() {
  return {imsrg::Parity::Even(), imsrg::Parity::Odd()};
}

static std::vector<imsrg::JJ_P_M_TT> ValidJJPMTTs(imsrg::TotalAngMom jjmax) {
  std::vector<imsrg::JJ_P_M_TT> valid;
  for (const auto m_tt : ValidM_TTs()) {
    for (const auto p : ValidPs()) {
      for (const auto jj : ValidJJs(jjmax)) {
        valid.push_back(imsrg::JJ_P_M_TT(jj, p, m_tt));
      }
    }
  }
  return valid;
}

static absl::flat_hash_map<imsrg::SPChannelKey,
                           std::shared_ptr<const imsrg::SPPartialBasis>>&
GetBasisPtrCache() {
  static absl::flat_hash_map<imsrg::SPChannelKey,
                             std::shared_ptr<const imsrg::SPPartialBasis>>
      partitioning;
  return partitioning;
}

static std::shared_ptr<const imsrg::SPPartialBasis> GetPartialBasisPtr(
    imsrg::SPChannelKey key) {
  auto& partitioning = GetBasisPtrCache();

  if (partitioning.find(key) == partitioning.end()) {
    partitioning[key] = std::make_shared<const imsrg::SPPartialBasis>(
        std::vector<imsrg::SPState>());
  }

  return partitioning[key];
}

static std::vector<imsrg::SPChannel> SampleChannels(imsrg::TotalAngMom jjmax) {
  std::vector<imsrg::SPChannel> valid;

  for (const auto jjpmtt : ValidJJPMTTs(jjmax)) {
    imsrg::SPChannelKey chan_key(jjpmtt);
    imsrg::SPChannel chan(chan_key, GetPartialBasisPtr(chan_key));

    valid.push_back(chan);
  }
  return valid;
}

template <typename T>
bool IsElemInVector(const T& e, const std::vector<T>& vec) {
  for (const auto& x : vec) {
    if (e == x) {
      return true;
    }
  }
  return false;
}

template <typename T>
bool IsVectorSorted(const std::vector<T>& vec) {
  for (std::size_t i = 1; i < vec.size(); i++) {
    if (vec[i] < vec[i - 1]) {
      return false;
    }
  }
  return true;
}

TEST_CASE("Test ctor and Channels().") {
  using imsrg::TotalAngMom;

  for (const auto jjmax : {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
    const auto chans = SampleChannels(jjmax);
    imsrg::SPModelSpace ms(chans);

    const auto& ms_chans = ms.Channels();

    REQUIRE(ms_chans.size() == chans.size());

    for (const auto& chan : chans) {
      REQUIRE(IsElemInVector(chan, ms_chans));
    }
  }
}

TEST_CASE("Test sorting of channels.") {
  using imsrg::TotalAngMom;

  for (const auto jjmax : {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
    const auto chans = SampleChannels(jjmax);
    imsrg::SPModelSpace ms(chans);

    const auto& ms_chans = ms.Channels();

    REQUIRE_FALSE(IsVectorSorted(chans));
    REQUIRE(IsVectorSorted(ms_chans));
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::SPModelSpace>::value);
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::SPModelSpace>::value);
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::SPModelSpace>::value);
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::SPModelSpace>::value);
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::SPModelSpace>::value);
}

TEST_CASE("Test member swap.") {
  using imsrg::TotalAngMom;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPModelSpace>::value);

  for (const auto jjmax1 : {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
    const auto chans1 = SampleChannels(jjmax1);
    for (const auto jjmax2 :
         {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
      const auto chans2 = SampleChannels(jjmax2);
      imsrg::SPModelSpace ms1(chans1);
      imsrg::SPModelSpace ms2(chans2);

      // Copies
      const auto ms1_chans = ms1.Channels();
      const auto ms2_chans = ms2.Channels();

      ms1.swap(ms2);

      REQUIRE(imsrg::test::AreVectorsEqual(ms2.Channels(), ms1_chans));
      REQUIRE(imsrg::test::AreVectorsEqual(ms1.Channels(), ms2_chans));
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using imsrg::TotalAngMom;
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPModelSpace>::value);

  for (const auto jjmax1 : {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
    const auto chans1 = SampleChannels(jjmax1);
    for (const auto jjmax2 :
         {TotalAngMom(9), TotalAngMom(15), TotalAngMom(45)}) {
      const auto chans2 = SampleChannels(jjmax2);
      imsrg::SPModelSpace ms1(chans1);
      imsrg::SPModelSpace ms2(chans2);

      // Copies
      const auto ms1_chans = ms1.Channels();
      const auto ms2_chans = ms2.Channels();

      swap(ms1, ms2);

      REQUIRE(imsrg::test::AreVectorsEqual(ms2.Channels(), ms1_chans));
      REQUIRE(imsrg::test::AreVectorsEqual(ms1.Channels(), ms2_chans));
    }
  }
}
