// Copyright 2022 Manhias Heinz
#include "imsrg/quantum_numbers/radial_excitation_number.h"

#include <type_traits>
#include <utility>

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::RadialExcitationNumber n_o(n);

    REQUIRE(n_o.AsInt() == n);
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::RadialExcitationNumber n_o(-1);

  REQUIRE(n_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::RadialExcitationNumber>::value);

  for (const auto& n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::RadialExcitationNumber n1(n);
    imsrg::RadialExcitationNumber n2(n1);

    REQUIRE(n1 == n2);
    REQUIRE(n1.AsInt() == n);
    REQUIRE(n2.AsInt() == n);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(
      std::is_nothrow_move_constructible<imsrg::RadialExcitationNumber>::value);

  for (const auto& n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::RadialExcitationNumber n1(n);
    imsrg::RadialExcitationNumber n2(std::move(n1));

    REQUIRE(n2.AsInt() == n);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::RadialExcitationNumber>::value);

  for (const auto& n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::RadialExcitationNumber n1(n);
    imsrg::RadialExcitationNumber n2(0);

    n2 = n1;

    REQUIRE(n1 == n2);
    REQUIRE(n1.AsInt() == n);
    REQUIRE(n2.AsInt() == n);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(
      std::is_nothrow_move_assignable<imsrg::RadialExcitationNumber>::value);

  for (const auto& n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::RadialExcitationNumber n1(n);
    imsrg::RadialExcitationNumber n2(0);

    n2 = std::move(n1);

    REQUIRE(n2.AsInt() == n);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::RadialExcitationNumber>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::RadialExcitationNumber>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE(n1.AsInt() == x1);
      REQUIRE(n2.AsInt() == x2);

      n1.swap(n2);

      REQUIRE(n1.AsInt() == x2);
      REQUIRE(n2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::RadialExcitationNumber>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE(n1.AsInt() == x1);
      REQUIRE(n2.AsInt() == x2);

      swap(n1, n2);

      REQUIRE(n1.AsInt() == x2);
      REQUIRE(n2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 < n2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 <= n2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 == n2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 > n2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 != n2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::RadialExcitationNumber n1(x1);
      imsrg::RadialExcitationNumber n2(x2);

      REQUIRE((n1 >= n2) == (x1 >= x2));
    }
  }
}
