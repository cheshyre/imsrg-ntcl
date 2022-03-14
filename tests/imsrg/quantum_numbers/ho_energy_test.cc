// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/ho_energy.h"

#include <type_traits>
#include <utility>
#include <vector>

#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"

#include "tests/helpers/equality.h"

#include "tests/catch.hpp"

// Helper function for checking membership
inline bool N_L_IsInVector(imsrg::N_L nl,
                           const std::vector<imsrg::N_L>& nl_vec) {
  for (const auto& [n2, l2] : nl_vec) {
    if ((nl.n == n2) && (nl.l == l2)) {
      return true;
    }
  }

  return false;
}

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& e : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::HOEnergy e_o(e);

    REQUIRE(e_o.AsInt() == e);
  }
}

TEST_CASE("Test n, l and l, n constructors.") {
  for (const auto& n : {0, 1, 2, 3, 4}) {
    imsrg::RadialExcitationNumber n_o(n);
    for (const auto& l : {0, 1, 2, 4, 5, 6, 7}) {
      imsrg::OrbitalAngMom l_o(l);

      imsrg::HOEnergy e1(n_o, l_o);
      imsrg::HOEnergy e2(n_o, l_o);

      REQUIRE(e1.AsInt() == 2 * n + l);
      REQUIRE(e2.AsInt() == 2 * n + l);
    }
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::HOEnergy e_o(-1);

  REQUIRE(e_o.AsInt() == -1);
}

TEST_CASE("Test GenerateSubShellQuantumNumbers for e=0.") {
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  std::vector<imsrg::N_L> expected = {
      {RadialExcitationNumber(0), OrbitalAngMom(0)}};

  imsrg::HOEnergy e(0);

  auto shells = e.GenerateSubShellQuantumNumbers();

  REQUIRE(shells.size() == expected.size());

  for (auto nl_exp : expected) {
    REQUIRE(N_L_IsInVector(nl_exp, shells));
  }
}

TEST_CASE("Test GenerateSubShellQuantumNumbers for e=1.") {
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  std::vector<imsrg::N_L> expected = {
      {RadialExcitationNumber(0), OrbitalAngMom(1)}};

  imsrg::HOEnergy e(1);

  auto shells = e.GenerateSubShellQuantumNumbers();

  REQUIRE(shells.size() == expected.size());

  for (auto nl_exp : expected) {
    REQUIRE(N_L_IsInVector(nl_exp, shells));
  }
}

TEST_CASE("Test GenerateSubShellQuantumNumbers for e=2.") {
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  std::vector<imsrg::N_L> expected = {
      {RadialExcitationNumber(1), OrbitalAngMom(0)},
      {RadialExcitationNumber(0), OrbitalAngMom(2)}};

  imsrg::HOEnergy e(2);

  auto shells = e.GenerateSubShellQuantumNumbers();

  REQUIRE(shells.size() == expected.size());

  for (auto nl_exp : expected) {
    REQUIRE(N_L_IsInVector(nl_exp, shells));
  }
}

TEST_CASE("Test GenerateSubShellQuantumNumbers for e=3.") {
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  std::vector<imsrg::N_L> expected = {
      {RadialExcitationNumber(1), OrbitalAngMom(1)},
      {RadialExcitationNumber(0), OrbitalAngMom(3)}};

  imsrg::HOEnergy e(3);

  auto shells = e.GenerateSubShellQuantumNumbers();

  REQUIRE(shells.size() == expected.size());

  for (auto nl_exp : expected) {
    REQUIRE(N_L_IsInVector(nl_exp, shells));
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::HOEnergy>::value);

  for (const auto& e : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::HOEnergy e1(e);
    imsrg::HOEnergy e2(e1);

    REQUIRE(e1 == e2);
    REQUIRE(e1.AsInt() == e);
    REQUIRE(e2.AsInt() == e);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::HOEnergy>::value);

  for (const auto& e : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::HOEnergy e1(e);
    imsrg::HOEnergy e2(std::move(e1));

    REQUIRE(e2.AsInt() == e);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::HOEnergy>::value);

  for (const auto& e : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::HOEnergy e1(e);
    imsrg::HOEnergy e2(0);

    e2 = e1;

    REQUIRE(e1 == e2);
    REQUIRE(e1.AsInt() == e);
    REQUIRE(e2.AsInt() == e);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::HOEnergy>::value);

  for (const auto& e : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::HOEnergy e1(e);
    imsrg::HOEnergy e2(0);

    e2 = std::move(e1);

    REQUIRE(e2.AsInt() == e);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::HOEnergy>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::HOEnergy>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE(e1.AsInt() == x1);
      REQUIRE(e2.AsInt() == x2);

      e1.swap(e2);

      REQUIRE(e1.AsInt() == x2);
      REQUIRE(e2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::HOEnergy>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE(e1.AsInt() == x1);
      REQUIRE(e2.AsInt() == x2);

      swap(e1, e2);

      REQUIRE(e1.AsInt() == x2);
      REQUIRE(e2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 < e2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 <= e2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 == e2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 > e2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 != e2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::HOEnergy e1(x1);
      imsrg::HOEnergy e2(x2);

      REQUIRE((e1 >= e2) == (x1 >= x2));
    }
  }
}

TEST_CASE("Test GenerateHOEnergyShells for emax=0.") {
  std::vector<imsrg::HOEnergy> expected = {imsrg::HOEnergy(0)};

  auto actual = imsrg::GenerateHOEnergyShells(imsrg::HOEnergy(0));

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test GenerateHOEnergyShells for emax=1.") {
  std::vector<imsrg::HOEnergy> expected = {imsrg::HOEnergy(0),
                                           imsrg::HOEnergy(1)};

  auto actual = imsrg::GenerateHOEnergyShells(imsrg::HOEnergy(1));

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test GenerateHOEnergyShells for emax=8.") {
  std::vector<imsrg::HOEnergy> expected = {
      imsrg::HOEnergy(0), imsrg::HOEnergy(1), imsrg::HOEnergy(2),
      imsrg::HOEnergy(3), imsrg::HOEnergy(4), imsrg::HOEnergy(5),
      imsrg::HOEnergy(6), imsrg::HOEnergy(7), imsrg::HOEnergy(8)};

  auto actual = imsrg::GenerateHOEnergyShells(imsrg::HOEnergy(8));

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}
