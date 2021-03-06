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

TEST_CASE("Test IsHalfInteger() and IsInteger() on even m_jj.") {
  for (const auto& m_jj : {-8, -6, -4, -2, 0, 2, 4, 6, 8}) {
    imsrg::M_JJ m_jj_o(m_jj);

    REQUIRE(m_jj_o.IsInteger());
    REQUIRE_FALSE(m_jj_o.IsHalfInteger());
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on odd m_jj.") {
  for (const auto& m_jj : {-9, -7, -5, -3, -1, 1, 3, 5, 7, 9}) {
    imsrg::M_JJ m_jj_o(m_jj);

    REQUIRE_FALSE(m_jj_o.IsInteger());
    REQUIRE(m_jj_o.IsHalfInteger());
  }
}

TEST_CASE("Test Phase() on even m_jj.") {
  for (const auto& m_jj : {-8, -6, -4, -2, 0, 2, 4, 6, 8}) {
    imsrg::M_JJ m_jj_o(m_jj);

    REQUIRE(m_jj_o.Phase().IsValidAsInt());
    if (m_jj % 4 == 0) {
      REQUIRE(m_jj_o.Phase().AsInt() == 1);
    } else {
      REQUIRE(m_jj_o.Phase().AsInt() == -1);
    }
  }
}

TEST_CASE("Test Phase() on odd m_jj.") {
  for (const auto& m_jj : {-9, -7, -5, -3, -1, 1, 3, 5, 7, 9}) {
    imsrg::M_JJ m_jj_o(m_jj);

    REQUIRE_FALSE(m_jj_o.Phase().IsValidAsInt());
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
