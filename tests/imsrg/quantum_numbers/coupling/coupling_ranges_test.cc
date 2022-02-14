// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"

#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/isospin.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

using imsrg::JJ;

TEST_CASE("Test 1/2 and 1/2.") {
  JJ a(1);
  JJ b(1);

  std::vector<JJ> expected = {JJ(0), JJ(2)};
  auto actual = imsrg::GenerateCouplingRange(a, b);

  REQUIRE(expected.size() == actual.size());

  for (std::size_t i = 0; i < expected.size(); i++) {
    REQUIRE(actual[i] == expected[i]);
  }

  REQUIRE(imsrg::CouplingMinimum(a, b) == JJ(0));
  REQUIRE(imsrg::CouplingMaximum(a, b) == JJ(2));
}

TEST_CASE("Test 1/2 and 0.") {
  JJ a(1);
  JJ b(0);

  std::vector<JJ> expected = {JJ(1)};
  SECTION("a, b.") {
    auto actual = imsrg::GenerateCouplingRange(a, b);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(a, b) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(a, b) == JJ(1));
  }
  SECTION("b, a.") {
    auto actual = imsrg::GenerateCouplingRange(b, a);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(b, a) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(b, a) == JJ(1));
  }
}

TEST_CASE("Test 1/2 and 1.") {
  JJ a(1);
  JJ b(2);

  std::vector<JJ> expected = {JJ(1), JJ(3)};
  SECTION("a, b.") {
    auto actual = imsrg::GenerateCouplingRange(a, b);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(a, b) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(a, b) == JJ(3));
  }
  SECTION("b, a.") {
    auto actual = imsrg::GenerateCouplingRange(b, a);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(b, a) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(b, a) == JJ(3));
  }
}

TEST_CASE("Test 5/2 and 3.") {
  JJ a(5);
  JJ b(6);

  std::vector<JJ> expected = {JJ(1), JJ(3), JJ(5), JJ(7), JJ(9), JJ(11)};
  SECTION("a, b.") {
    auto actual = imsrg::GenerateCouplingRange(a, b);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(a, b) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(a, b) == JJ(11));
  }
  SECTION("b, a.") {
    auto actual = imsrg::GenerateCouplingRange(b, a);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }

    REQUIRE(imsrg::CouplingMinimum(b, a) == JJ(1));
    REQUIRE(imsrg::CouplingMaximum(b, a) == JJ(11));
  }
}

TEST_CASE("Test CouplingRangeFromMinAndMax (1/2 to 11/2).") {
  JJ min_jj(1);
  JJ max_jj(11);

  std::vector<JJ> expected = {JJ(1), JJ(3), JJ(5), JJ(7), JJ(9), JJ(11)};
  auto actual = imsrg::CouplingRangeFromMinAndMax(min_jj, max_jj);

  REQUIRE(expected.size() == actual.size());

  for (std::size_t i = 0; i < expected.size(); i++) {
    REQUIRE(actual[i] == expected[i]);
  }
}

TEST_CASE("Test zero orbital angular momentum and spin 1/2 (order=l,s).") {
  using imsrg::OrbitalAngMom;
  using imsrg::Spin;
  using imsrg::TotalAngMom;

  SECTION("with explicit return type.") {
    OrbitalAngMom l(0);
    auto s = Spin::OneHalf();

    std::vector<TotalAngMom> expected = {TotalAngMom(1)};
    std::vector<TotalAngMom> actual =
        imsrg::GenerateCouplingRange<TotalAngMom>(l, s);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }
  }

  SECTION("with deduced return type.") {
    OrbitalAngMom l(0);
    auto s = Spin::OneHalf();

    std::vector<TotalAngMom> expected = {TotalAngMom(1)};
    auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(l, s);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }
  }
}

TEST_CASE("Test nonzero orbital angular momentum and spin 1/2 (order=l,s).") {
  using imsrg::OrbitalAngMom;
  using imsrg::Spin;
  using imsrg::TotalAngMom;

  SECTION("with explicit return type.") {
    for (const auto l_i : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      OrbitalAngMom l(l_i);
      auto s = Spin::OneHalf();

      std::vector<TotalAngMom> expected = {TotalAngMom(2 * l_i - 1),
                                           TotalAngMom(2 * l_i + 1)};
      std::vector<TotalAngMom> actual =
          imsrg::GenerateCouplingRange<TotalAngMom>(l, s);

      REQUIRE(expected.size() == actual.size());

      for (std::size_t i = 0; i < expected.size(); i++) {
        REQUIRE(actual[i] == expected[i]);
      }
    }
  }

  SECTION("with deduced return type.") {
    for (const auto l_i : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      OrbitalAngMom l(l_i);
      auto s = Spin::OneHalf();

      std::vector<TotalAngMom> expected = {TotalAngMom(2 * l_i - 1),
                                           TotalAngMom(2 * l_i + 1)};
      auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(l, s);

      REQUIRE(expected.size() == actual.size());

      for (std::size_t i = 0; i < expected.size(); i++) {
        REQUIRE(actual[i] == expected[i]);
      }
    }
  }
}

TEST_CASE("Test zero orbital angular momentum and spin 1/2 (order=s,l).") {
  using imsrg::OrbitalAngMom;
  using imsrg::Spin;
  using imsrg::TotalAngMom;

  SECTION("with explicit return type.") {
    OrbitalAngMom l(0);
    auto s = Spin::OneHalf();

    std::vector<TotalAngMom> expected = {TotalAngMom(1)};
    std::vector<TotalAngMom> actual =
        imsrg::GenerateCouplingRange<TotalAngMom>(s, l);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }
  }

  SECTION("with deduced return type.") {
    OrbitalAngMom l(0);
    auto s = Spin::OneHalf();

    std::vector<TotalAngMom> expected = {TotalAngMom(1)};
    auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(s, l);

    REQUIRE(expected.size() == actual.size());

    for (std::size_t i = 0; i < expected.size(); i++) {
      REQUIRE(actual[i] == expected[i]);
    }
  }
}

TEST_CASE("Test nonzero orbital angular momentum and spin 1/2 (order=s,l).") {
  using imsrg::OrbitalAngMom;
  using imsrg::Spin;
  using imsrg::TotalAngMom;

  SECTION("with explicit return type.") {
    for (const auto l_i : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      OrbitalAngMom l(l_i);
      auto s = Spin::OneHalf();

      std::vector<TotalAngMom> expected = {TotalAngMom(2 * l_i - 1),
                                           TotalAngMom(2 * l_i + 1)};
      std::vector<TotalAngMom> actual =
          imsrg::GenerateCouplingRange<TotalAngMom>(s, l);

      REQUIRE(expected.size() == actual.size());

      for (std::size_t i = 0; i < expected.size(); i++) {
        REQUIRE(actual[i] == expected[i]);
      }
    }
  }

  SECTION("with deduced return type.") {
    for (const auto l_i : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      OrbitalAngMom l(l_i);
      auto s = Spin::OneHalf();

      std::vector<TotalAngMom> expected = {TotalAngMom(2 * l_i - 1),
                                           TotalAngMom(2 * l_i + 1)};
      auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(s, l);

      REQUIRE(expected.size() == actual.size());

      for (std::size_t i = 0; i < expected.size(); i++) {
        REQUIRE(actual[i] == expected[i]);
      }
    }
  }
}

TEST_CASE("Test total angular momentum coupling (5/2, 3/2).") {
  using imsrg::TotalAngMom;

  TotalAngMom a(5);
  TotalAngMom b(3);

  std::vector<TotalAngMom> expected = {TotalAngMom(2), TotalAngMom(4),
                                       TotalAngMom(6), TotalAngMom(8)};
  auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(a, b);

  REQUIRE(expected.size() == actual.size());

  for (std::size_t i = 0; i < expected.size(); i++) {
    REQUIRE(actual[i] == expected[i]);
  }
}

TEST_CASE("Test total angular momentum coupling (5/2, 5/2).") {
  using imsrg::TotalAngMom;

  TotalAngMom a(5);
  TotalAngMom b(5);

  std::vector<TotalAngMom> expected = {TotalAngMom(0), TotalAngMom(2),
                                       TotalAngMom(4), TotalAngMom(6),
                                       TotalAngMom(8), TotalAngMom(10)};
  auto actual = imsrg::GenerateCouplingRange<TotalAngMom>(a, b);

  REQUIRE(expected.size() == actual.size());

  for (std::size_t i = 0; i < expected.size(); i++) {
    REQUIRE(actual[i] == expected[i]);
  }
}

TEST_CASE("Test nucleon nucleon isospin coupling.") {
  using imsrg::Isospin;

  auto a = Isospin::Nucleon();
  auto b = Isospin::Nucleon();

  std::vector<Isospin> expected = {Isospin(0), Isospin(2)};
  auto actual = imsrg::GenerateCouplingRange<Isospin>(a, b);

  REQUIRE(expected.size() == actual.size());

  for (std::size_t i = 0; i < expected.size(); i++) {
    REQUIRE(actual[i] == expected[i]);
  }
}
