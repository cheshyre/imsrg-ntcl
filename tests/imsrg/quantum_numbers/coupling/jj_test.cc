// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/jj.h"

#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/phases.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj_o(jj);

    REQUIRE(jj_o.AsInt() == jj);
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on even jj.") {
  for (const auto& jj : {0, 2, 4, 6, 8}) {
    imsrg::JJ jj_o(jj);

    REQUIRE(jj_o.IsInteger());
    REQUIRE_FALSE(jj_o.IsHalfInteger());
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on odd jj.") {
  for (const auto& jj : {1, 3, 5, 7, 9}) {
    imsrg::JJ jj_o(jj);

    REQUIRE_FALSE(jj_o.IsInteger());
    REQUIRE(jj_o.IsHalfInteger());
  }
}

TEST_CASE("Test Phase() on even jj.") {
  for (const auto& jj : {0, 2, 4, 6, 8}) {
    imsrg::JJ jj_o(jj);

    REQUIRE(jj_o.Phase().IsValidAsInt());
    if (jj % 4 == 0) {
      REQUIRE(jj_o.Phase().AsInt() == 1);
    } else {
      REQUIRE(jj_o.Phase().AsInt() == -1);
    }
  }
}

TEST_CASE("Test Phase() on odd jj.") {
  for (const auto& jj : {1, 3, 5, 7, 9}) {
    imsrg::JJ jj_o(jj);

    REQUIRE_FALSE(jj_o.Phase().IsValidAsInt());
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::JJ jj_o(-1);

  REQUIRE(jj_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::JJ>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj1(jj);
    imsrg::JJ jj2(jj1);

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::JJ>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj1(jj);
    imsrg::JJ jj2(std::move(jj1));

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::JJ>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj1(jj);
    imsrg::JJ jj2(0);

    jj2 = jj1;

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::JJ>::value);

  for (const auto& jj : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj1(jj);
    imsrg::JJ jj2(0);

    jj2 = std::move(jj1);

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::JJ>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::JJ>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

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
  REQUIRE(std::is_nothrow_swappable<imsrg::JJ>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

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
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 < jj2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 <= jj2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 == jj2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 > jj2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 != jj2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::JJ jj1(x1);
      imsrg::JJ jj2(x2);

      REQUIRE((jj1 >= jj2) == (x1 >= x2));
    }
  }
}
