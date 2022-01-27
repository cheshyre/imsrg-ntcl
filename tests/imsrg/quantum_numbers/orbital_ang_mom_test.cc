// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/orbital_ang_mom.h"

#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/jj.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::OrbitalAngMom l_o(l);

    REQUIRE(l_o.AsInt() == l);
  }
}

TEST_CASE("Test JJ constructor and AsJJ().") {
  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ ll_p(2 * l);
    imsrg::OrbitalAngMom l_o(ll_p);

    REQUIRE(l_o.AsJJ() == ll_p);
  }
}

TEST_CASE("Test odd JJ constructor.", "[!hide][!shouldfail]") {
  imsrg::JJ ll_p(1);
  imsrg::OrbitalAngMom l_o(ll_p);

  REQUIRE(l_o.AsJJ() == ll_p);
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::OrbitalAngMom l_o(-1);

  REQUIRE(l_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::OrbitalAngMom>::value);

  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::OrbitalAngMom l1(l);
    imsrg::OrbitalAngMom l2(l1);

    REQUIRE(l1 == l2);
    REQUIRE(l1.AsInt() == l);
    REQUIRE(l2.AsInt() == l);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::OrbitalAngMom>::value);

  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::OrbitalAngMom l1(l);
    imsrg::OrbitalAngMom l2(std::move(l1));

    REQUIRE(l2.AsInt() == l);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::OrbitalAngMom>::value);

  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::OrbitalAngMom l1(l);
    imsrg::OrbitalAngMom l2(0);

    l2 = l1;

    REQUIRE(l1 == l2);
    REQUIRE(l1.AsInt() == l);
    REQUIRE(l2.AsInt() == l);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::OrbitalAngMom>::value);

  for (const auto& l : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::OrbitalAngMom l1(l);
    imsrg::OrbitalAngMom l2(0);

    l2 = std::move(l1);

    REQUIRE(l2.AsInt() == l);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::OrbitalAngMom>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::OrbitalAngMom>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE(l1.AsInt() == x1);
      REQUIRE(l2.AsInt() == x2);

      l1.swap(l2);

      REQUIRE(l1.AsInt() == x2);
      REQUIRE(l2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::OrbitalAngMom>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE(l1.AsInt() == x1);
      REQUIRE(l2.AsInt() == x2);

      swap(l1, l2);

      REQUIRE(l1.AsInt() == x2);
      REQUIRE(l2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 < l2) == (imsrg::JJ(x1) < imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 <= l2) == (imsrg::JJ(x1) <= imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 == l2) == (imsrg::JJ(x1) == imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 > l2) == (imsrg::JJ(x1) > imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 != l2) == (imsrg::JJ(x1) != imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::OrbitalAngMom l1(x1);
      imsrg::OrbitalAngMom l2(x2);

      REQUIRE((l1 >= l2) == (imsrg::JJ(x1) >= imsrg::JJ(x2)));
    }
  }
}
