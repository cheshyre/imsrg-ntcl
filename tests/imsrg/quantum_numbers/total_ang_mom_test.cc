// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include <type_traits>
#include <utility>

#include "absl/hash/hash_testing.h"

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

TEST_CASE("Test IsHalfInteger() and IsInteger() on even jj.") {
  for (const auto& jj : {0, 2, 4, 6, 8}) {
    imsrg::TotalAngMom jj_o(jj);

    REQUIRE(jj_o.IsInteger());
    REQUIRE_FALSE(jj_o.IsHalfInteger());
  }
}

TEST_CASE("Test IsHalfInteger() and IsInteger() on odd jj.") {
  for (const auto& jj : {1, 3, 5, 7, 9}) {
    imsrg::TotalAngMom jj_o(jj);

    REQUIRE_FALSE(jj_o.IsInteger());
    REQUIRE(jj_o.IsHalfInteger());
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

TEST_CASE("Test proper abseil hash.") {
  using imsrg::TotalAngMom;
  REQUIRE(absl::VerifyTypeImplementsAbslHashCorrectly(
      {TotalAngMom(0),  TotalAngMom(1),  TotalAngMom(2),  TotalAngMom(3),
       TotalAngMom(4),  TotalAngMom(5),  TotalAngMom(6),  TotalAngMom(7),
       TotalAngMom(8),  TotalAngMom(9),  TotalAngMom(10), TotalAngMom(11),
       TotalAngMom(12), TotalAngMom(13), TotalAngMom(14), TotalAngMom(15),
       TotalAngMom(16), TotalAngMom(17), TotalAngMom(18), TotalAngMom(19),
       TotalAngMom(20), TotalAngMom(21), TotalAngMom(22), TotalAngMom(23),
       TotalAngMom(24), TotalAngMom(25), TotalAngMom(26), TotalAngMom(27),
       TotalAngMom(28), TotalAngMom(29), TotalAngMom(30)}));
}
