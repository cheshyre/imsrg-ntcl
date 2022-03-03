// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/phases.h"

#include <type_traits>

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

TEST_CASE("Test even J have phase == 1.") {
  using imsrg::JJPhase;

  SECTION("Prefactor = 1") {
    for (const auto j : {-4, -2, 0, 2, 4}) {
      JJPhase phase(2 * j);

      REQUIRE(phase.IsValidAsInt());
      REQUIRE(phase.AsInt() == 1);
    }
  }

  SECTION("Prefactor = -1") {
    for (const auto j : {-4, -2, 0, 2, 4}) {
      JJPhase phase(2 * j, -1);

      REQUIRE(phase.IsValidAsInt());
      REQUIRE(phase.AsInt() == 1);
    }
  }
}

TEST_CASE("Test odd J have phase == -1.") {
  using imsrg::JJPhase;

  SECTION("Prefactor = 1") {
    for (const auto j : {-3, -1, 1, 3, 5}) {
      JJPhase phase(2 * j);

      REQUIRE(phase.IsValidAsInt());
      REQUIRE(phase.AsInt() == -1);
    }
  }

  SECTION("Prefactor = -1") {
    for (const auto j : {-3, -1, 1, 3, 5}) {
      JJPhase phase(2 * j, -1);

      REQUIRE(phase.IsValidAsInt());
      REQUIRE(phase.AsInt() == -1);
    }
  }
}

TEST_CASE("Test One() factory method.") {
  REQUIRE(imsrg::JJPhase::One().IsValidAsInt());
  REQUIRE(imsrg::JJPhase::One().AsInt() == 1);
}

TEST_CASE("Test MinusOne() factory method.") {
  REQUIRE(imsrg::JJPhase::MinusOne().IsValidAsInt());
  REQUIRE(imsrg::JJPhase::MinusOne().AsInt() == -1);
}

TEST_CASE("Test odd JJ (half-integer J) are not valid as int.") {
  using imsrg::JJPhase;

  SECTION("Prefactor = 1") {
    for (const auto jj : {-3, -1, 1, 3, 5}) {
      JJPhase phase(jj);

      REQUIRE_FALSE(phase.IsValidAsInt());
    }
  }

  SECTION("Prefactor = -1") {
    for (const auto jj : {-3, -1, 1, 3, 5}) {
      JJPhase phase(jj, -1);

      REQUIRE_FALSE(phase.IsValidAsInt());
    }
  }
}

TEST_CASE("Test odd jj phases squared.") {
  using imsrg::JJPhase;

  for (const auto jj : {-3, -1, 1, 3, 5}) {
    JJPhase phase_1(jj);
    JJPhase phase_m1(jj, -1);

    JJPhase phase_squared_1(2 * jj);
    JJPhase phase_squared_m1(2 * jj, -1);

    const auto phase_1_1 = phase_1 * phase_1;
    const auto phase_1_m1 = phase_1 * phase_m1;
    const auto phase_m1_m1 = phase_m1 * phase_m1;
    const auto phase_m1_1 = phase_m1 * phase_1;

    REQUIRE(phase_1_1.IsValidAsInt());
    REQUIRE(phase_1_1.AsInt() == phase_squared_1.AsInt());
    REQUIRE(phase_1_m1.IsValidAsInt());
    REQUIRE(phase_1_m1.AsInt() == JJPhase::One().AsInt());
    REQUIRE(phase_m1_m1.IsValidAsInt());
    REQUIRE(phase_m1_m1.AsInt() == phase_squared_m1.AsInt());
    REQUIRE(phase_m1_1.IsValidAsInt());
    REQUIRE(phase_m1_1.AsInt() == JJPhase::One().AsInt());
  }
}

TEST_CASE("Test copy constructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::JJPhase>::value);
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::JJPhase>::value);
}

TEST_CASE("Test move constructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::JJPhase>::value);
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::JJPhase>::value);
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::JJPhase>::value);
}

TEST_CASE("Test swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::JJPhase>::value);
}
