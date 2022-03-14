// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/spin.h"

#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/jj.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Spin ss_o(ss);

    REQUIRE(ss_o.AsInt() == ss);
  }
}

TEST_CASE("Test JJ constructor and AsJJ().") {
  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj_p(ss);
    imsrg::Spin ss_o(jj_p);

    REQUIRE(ss_o.AsJJ() == jj_p);
  }
}

TEST_CASE("Test spin 1/2 static constructor.") {
  auto s = imsrg::Spin::OneHalf();

  REQUIRE(s == imsrg::Spin(1));
  REQUIRE(s.AsJJ() == imsrg::JJ(1));
  REQUIRE(s.AsInt() == 1);
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on even ss.") {
  for (const auto& ss : {0, 2, 4, 6, 8}) {
    imsrg::Spin ss_o(ss);

    REQUIRE(ss_o.IsInteger());
    REQUIRE_FALSE(ss_o.IsHalfInteger());
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on odd ss.") {
  for (const auto& ss : {1, 3, 5, 7, 9}) {
    imsrg::Spin ss_o(ss);

    REQUIRE_FALSE(ss_o.IsInteger());
    REQUIRE(ss_o.IsHalfInteger());
  }
}

TEST_CASE("Test Phase() on even ss.") {
  for (const auto& ss : {0, 2, 4, 6, 8}) {
    imsrg::Spin ss_o(ss);

    REQUIRE(ss_o.Phase().IsValidAsInt());
    if (ss % 4 == 0) {
      REQUIRE(ss_o.Phase().AsInt() == 1);
    } else {
      REQUIRE(ss_o.Phase().AsInt() == -1);
    }
  }
}

TEST_CASE("Test Phase() on odd ss.") {
  for (const auto& ss : {1, 3, 5, 7, 9}) {
    imsrg::Spin ss_o(ss);

    REQUIRE_FALSE(ss_o.Phase().IsValidAsInt());
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::Spin ss_o(-1);

  REQUIRE(ss_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::Spin>::value);

  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Spin ss1(ss);
    imsrg::Spin ss2(ss1);

    REQUIRE(ss1 == ss2);
    REQUIRE(ss1.AsInt() == ss);
    REQUIRE(ss2.AsInt() == ss);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::Spin>::value);

  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Spin ss1(ss);
    imsrg::Spin ss2(std::move(ss1));

    REQUIRE(ss2.AsInt() == ss);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::Spin>::value);

  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Spin ss1(ss);
    imsrg::Spin ss2(0);

    ss2 = ss1;

    REQUIRE(ss1 == ss2);
    REQUIRE(ss1.AsInt() == ss);
    REQUIRE(ss2.AsInt() == ss);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::Spin>::value);

  for (const auto& ss : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Spin ss1(ss);
    imsrg::Spin ss2(0);

    ss2 = std::move(ss1);

    REQUIRE(ss2.AsInt() == ss);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::Spin>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::Spin>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE(ss1.AsInt() == x1);
      REQUIRE(ss2.AsInt() == x2);

      ss1.swap(ss2);

      REQUIRE(ss1.AsInt() == x2);
      REQUIRE(ss2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::Spin>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE(ss1.AsInt() == x1);
      REQUIRE(ss2.AsInt() == x2);

      swap(ss1, ss2);

      REQUIRE(ss1.AsInt() == x2);
      REQUIRE(ss2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 < ss2) == (imsrg::JJ(x1) < imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 <= ss2) == (imsrg::JJ(x1) <= imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 == ss2) == (imsrg::JJ(x1) == imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 > ss2) == (imsrg::JJ(x1) > imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 != ss2) == (imsrg::JJ(x1) != imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Spin ss1(x1);
      imsrg::Spin ss2(x2);

      REQUIRE((ss1 >= ss2) == (imsrg::JJ(x1) >= imsrg::JJ(x2)));
    }
  }
}
