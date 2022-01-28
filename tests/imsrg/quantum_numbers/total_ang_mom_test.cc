// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/jj.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::TotalAngMom jj_o(jj);

    REQUIRE(jj_o.AsInt() == jj);
  }
}

TEST_CASE("Test JJ constructor and AsJJ().") {
  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj_p(jj);
    imsrg::TotalAngMom jj_o(jj_p);

    REQUIRE(jj_o.AsJJ() == jj_p);
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj_o(-1);

  REQUIRE(jj_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::TotalAngMom>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::TotalAngMom jj1(jj);
    imsrg::TotalAngMom jj2(jj1);

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::TotalAngMom>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::TotalAngMom jj1(jj);
    imsrg::TotalAngMom jj2(std::move(jj1));

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::TotalAngMom>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::TotalAngMom jj1(jj);
    imsrg::TotalAngMom jj2(0);

    jj2 = jj1;

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::TotalAngMom>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::TotalAngMom jj1(jj);
    imsrg::TotalAngMom jj2(0);

    jj2 = std::move(jj1);

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::TotalAngMom>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::TotalAngMom>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE(jj1.AsInt() == x1);
      REQUIRE(jj2.AsInt() == x2);

      jj1.swap(jj2);

      REQUIRE(jj1.AsInt() == x2);
      REQUIRE(jj2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::TotalAngMom>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE(jj1.AsInt() == x1);
      REQUIRE(jj2.AsInt() == x2);

      swap(jj1, jj2);

      REQUIRE(jj1.AsInt() == x2);
      REQUIRE(jj2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 < jj2) == (imsrg::JJ(x1) < imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 <= jj2) == (imsrg::JJ(x1) <= imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 == jj2) == (imsrg::JJ(x1) == imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 > jj2) == (imsrg::JJ(x1) > imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 != jj2) == (imsrg::JJ(x1) != imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::TotalAngMom jj1(x1);
      imsrg::TotalAngMom jj2(x2);

      REQUIRE((jj1 >= jj2) == (imsrg::JJ(x1) >= imsrg::JJ(x2)));
    }
  }
}
