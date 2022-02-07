// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/occupation_number.h"

#include <type_traits>
#include <utility>

#include "tests/catch.hpp"

TEST_CASE("Test double constructor and AsDouble().") {
  for (const auto& n :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    imsrg::OccupationNumber n_o(n);

    REQUIRE(n_o.AsDouble() == n);
  }
}

TEST_CASE("Test negative double constructor.", "[!hide][!shouldfail]") {
  imsrg::OccupationNumber n_o(-0.25);

  REQUIRE(n_o.AsDouble() == -0.25);
}

TEST_CASE("Test >1 double constructor.", "[!hide][!shouldfail]") {
  imsrg::OccupationNumber n_o(1.25);

  REQUIRE(n_o.AsDouble() == 1.25);
}

TEST_CASE("Test 0 occupation is particle.") {
  imsrg::OccupationNumber n_o(0.0);

  REQUIRE(!n_o.IsHole());
  REQUIRE(n_o.IsParticle());
  REQUIRE(!n_o.IsValence());
}

TEST_CASE("Test fractional occupation is valence.") {
  for (const auto& n : {1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10}) {
    imsrg::OccupationNumber n_o(n);

    REQUIRE(!n_o.IsHole());
    REQUIRE(!n_o.IsParticle());
    REQUIRE(n_o.IsValence());
  }
}

TEST_CASE("Test 1 occupation is hole.") {
  imsrg::OccupationNumber n_o(1.0);

  REQUIRE(n_o.IsHole());
  REQUIRE(!n_o.IsParticle());
  REQUIRE(!n_o.IsValence());
}

TEST_CASE("Test hole static factory constructor.") {
  auto n_o = imsrg::OccupationNumber::Hole();

  REQUIRE(n_o.IsHole());
  REQUIRE(!n_o.IsParticle());
  REQUIRE(!n_o.IsValence());
}

TEST_CASE("Test particle static factory constructor.") {
  auto n_o = imsrg::OccupationNumber::Particle();

  REQUIRE(!n_o.IsHole());
  REQUIRE(n_o.IsParticle());
  REQUIRE(!n_o.IsValence());
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::OccupationNumber>::value);

  for (const auto& n :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    imsrg::OccupationNumber n1(n);
    imsrg::OccupationNumber n2(n1);

    REQUIRE(n1 == n2);
    REQUIRE(n1.AsDouble() == n);
    REQUIRE(n2.AsDouble() == n);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::OccupationNumber>::value);

  for (const auto& n :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    imsrg::OccupationNumber n1(n);
    imsrg::OccupationNumber n2(std::move(n1));

    REQUIRE(n2.AsDouble() == n);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::OccupationNumber>::value);

  for (const auto& n :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    imsrg::OccupationNumber n1(n);
    imsrg::OccupationNumber n2(0);

    n2 = n1;

    REQUIRE(n1 == n2);
    REQUIRE(n1.AsDouble() == n);
    REQUIRE(n2.AsDouble() == n);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::OccupationNumber>::value);

  for (const auto& n :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    imsrg::OccupationNumber n1(n);
    imsrg::OccupationNumber n2(0);

    n2 = std::move(n1);

    REQUIRE(n2.AsDouble() == n);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::OccupationNumber>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::OccupationNumber>::value);

  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE(n1.AsDouble() == x1);
      REQUIRE(n2.AsDouble() == x2);

      n1.swap(n2);

      REQUIRE(n1.AsDouble() == x2);
      REQUIRE(n2.AsDouble() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::OccupationNumber>::value);

  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE(n1.AsDouble() == x1);
      REQUIRE(n2.AsDouble() == x2);

      swap(n1, n2);

      REQUIRE(n1.AsDouble() == x2);
      REQUIRE(n2.AsDouble() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 < n2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 <= n2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 == n2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 > n2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 != n2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 :
       {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
    for (const auto& x2 :
         {0.0, 1.0 / 2, 1.0 / 4, 1.0 / 6, 1.0 / 8, 1.0 / 10, 1.0}) {
      imsrg::OccupationNumber n1(x1);
      imsrg::OccupationNumber n2(x2);

      REQUIRE((n1 >= n2) == (x1 >= x2));
    }
  }
}
