// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/isospin.h"

#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/jj.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Isospin tt_o(tt);

    REQUIRE(tt_o.AsInt() == tt);
  }
}

TEST_CASE("Test JJ constructor and AsJJ().") {
  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::JJ jj_p(tt);
    imsrg::Isospin tt_o(jj_p);

    REQUIRE(tt_o.AsJJ() == jj_p);
  }
}

TEST_CASE("Test nucleon static constructor.") {
  auto s = imsrg::Isospin::Nucleon();

  REQUIRE(s == imsrg::Isospin(1));
  REQUIRE(s.AsJJ() == imsrg::JJ(1));
  REQUIRE(s.AsInt() == 1);
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on even tt.") {
  for (const auto& tt : {0, 2, 4, 6, 8}) {
    imsrg::Isospin tt_o(tt);

    REQUIRE(tt_o.IsInteger());
    REQUIRE_FALSE(tt_o.IsHalfInteger());
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on odd tt.") {
  for (const auto& tt : {1, 3, 5, 7, 9}) {
    imsrg::Isospin tt_o(tt);

    REQUIRE_FALSE(tt_o.IsInteger());
    REQUIRE(tt_o.IsHalfInteger());
  }
}

TEST_CASE("Test Phase() on even tt.") {
  for (const auto& tt : {0, 2, 4, 6, 8}) {
    imsrg::Isospin tt_o(tt);

    REQUIRE(tt_o.Phase().IsValidAsInt());
    if (tt % 4 == 0) {
      REQUIRE(tt_o.Phase().AsInt() == 1);
    } else {
      REQUIRE(tt_o.Phase().AsInt() == -1);
    }
  }
}

TEST_CASE("Test Phase() on odd tt.") {
  for (const auto& tt : {1, 3, 5, 7, 9}) {
    imsrg::Isospin tt_o(tt);

    REQUIRE_FALSE(tt_o.Phase().IsValidAsInt());
  }
}

TEST_CASE("Test negative int constructor.", "[!hide][!shouldfail]") {
  imsrg::Isospin tt_o(-1);

  REQUIRE(tt_o.AsInt() == -1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::Isospin>::value);

  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Isospin tt1(tt);
    imsrg::Isospin tt2(tt1);

    REQUIRE(tt1 == tt2);
    REQUIRE(tt1.AsInt() == tt);
    REQUIRE(tt2.AsInt() == tt);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::Isospin>::value);

  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Isospin tt1(tt);
    imsrg::Isospin tt2(std::move(tt1));

    REQUIRE(tt2.AsInt() == tt);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::Isospin>::value);

  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Isospin tt1(tt);
    imsrg::Isospin tt2(0);

    tt2 = tt1;

    REQUIRE(tt1 == tt2);
    REQUIRE(tt1.AsInt() == tt);
    REQUIRE(tt2.AsInt() == tt);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::Isospin>::value);

  for (const auto& tt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::Isospin tt1(tt);
    imsrg::Isospin tt2(0);

    tt2 = std::move(tt1);

    REQUIRE(tt2.AsInt() == tt);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::Isospin>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::Isospin>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE(tt1.AsInt() == x1);
      REQUIRE(tt2.AsInt() == x2);

      tt1.swap(tt2);

      REQUIRE(tt1.AsInt() == x2);
      REQUIRE(tt2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::Isospin>::value);

  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE(tt1.AsInt() == x1);
      REQUIRE(tt2.AsInt() == x2);

      swap(tt1, tt2);

      REQUIRE(tt1.AsInt() == x2);
      REQUIRE(tt2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 < tt2) == (imsrg::JJ(x1) < imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 <= tt2) == (imsrg::JJ(x1) <= imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 == tt2) == (imsrg::JJ(x1) == imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 > tt2) == (imsrg::JJ(x1) > imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 != tt2) == (imsrg::JJ(x1) != imsrg::JJ(x2)));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::Isospin tt1(x1);
      imsrg::Isospin tt2(x2);

      REQUIRE((tt1 >= tt2) == (imsrg::JJ(x1) >= imsrg::JJ(x2)));
    }
  }
}
