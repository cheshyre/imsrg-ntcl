// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/m_jj.h"

#include <type_traits>
#include <utility>

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ jj_o(jj);

    REQUIRE(jj_o.AsInt() == jj);
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::M_JJ>::value);

  for (const auto& jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ jj1(jj);
    imsrg::M_JJ jj2(jj1);

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::M_JJ>::value);

  for (const auto& jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ jj1(jj);
    imsrg::M_JJ jj2(std::move(jj1));

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::M_JJ>::value);

  for (const auto& jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ jj1(jj);
    imsrg::M_JJ jj2(0);

    jj2 = jj1;

    REQUIRE(jj1 == jj2);
    REQUIRE(jj1.AsInt() == jj);
    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::M_JJ>::value);

  for (const auto& jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ jj1(jj);
    imsrg::M_JJ jj2(0);

    jj2 = std::move(jj1);

    REQUIRE(jj2.AsInt() == jj);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::M_JJ>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::M_JJ>::value);

  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

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
  REQUIRE(std::is_nothrow_swappable<imsrg::M_JJ>::value);

  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE(jj1.AsInt() == x1);
      REQUIRE(jj2.AsInt() == x2);

      swap(jj1, jj2);

      REQUIRE(jj1.AsInt() == x2);
      REQUIRE(jj2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 < jj2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 <= jj2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 == jj2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 > jj2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 != jj2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE((jj1 >= jj2) == (x1 >= x2));
    }
  }
}

TEST_CASE("Test operator+.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE(jj1.AsInt() == x1);
      REQUIRE(jj2.AsInt() == x2);

      auto jj3 = jj1 + jj2;

      REQUIRE(jj3.AsInt() == x1 + x2);
    }
  }
}

TEST_CASE("Test operator-.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::M_JJ jj1(x1);
      imsrg::M_JJ jj2(x2);

      REQUIRE(jj1.AsInt() == x1);
      REQUIRE(jj2.AsInt() == x2);

      auto jj3 = jj1 - jj2;
      auto jj4 = jj2 - jj1;

      REQUIRE(jj3.AsInt() == x1 - x2);
      REQUIRE(jj4.AsInt() == x2 - x1);
    }
  }
}
