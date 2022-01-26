// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/parity.h"

#include <array>
#include <type_traits>
#include <utility>

#include "tests/catch.hpp"

TEST_CASE("Test Even factory function with IsEven/IsOdd.") {
  auto p = imsrg::Parity::Even();

  REQUIRE(p.IsEven());
  REQUIRE_FALSE(p.IsOdd());
}

TEST_CASE("Test Odd factory function with IsEven/IsOdd.") {
  auto p = imsrg::Parity::Odd();

  REQUIRE(p.IsOdd());
  REQUIRE_FALSE(p.IsEven());
}

TEST_CASE("Test copy constructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::Parity>::value);

  SECTION("Even.") {
    auto p1 = imsrg::Parity::Even();
    imsrg::Parity p2(p1);

    REQUIRE(p1.IsEven());
    REQUIRE(p2.IsEven());
    REQUIRE(p1 == p2);
  }

  SECTION("Odd.") {
    auto p1 = imsrg::Parity::Odd();
    imsrg::Parity p2(p1);

    REQUIRE(p1.IsOdd());
    REQUIRE(p2.IsOdd());
    REQUIRE(p1 == p2);
  }
}

TEST_CASE("Test move constructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::Parity>::value);

  SECTION("Even.") {
    auto p1 = imsrg::Parity::Even();
    imsrg::Parity p2(std::move(p1));

    REQUIRE(p2.IsEven());
  }

  SECTION("Odd.") {
    auto p1 = imsrg::Parity::Odd();
    imsrg::Parity p2(std::move(p1));

    REQUIRE(p2.IsOdd());
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::Parity>::value);

  SECTION("Even.") {
    auto p1 = imsrg::Parity::Even();

    for (auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      p2 = p1;

      REQUIRE(p1.IsEven());
      REQUIRE(p2.IsEven());
      REQUIRE(p1 == p2);
    }
  }

  SECTION("Odd.") {
    auto p1 = imsrg::Parity::Odd();

    for (auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      p2 = p1;

      REQUIRE(p1.IsOdd());
      REQUIRE(p2.IsOdd());
      REQUIRE(p1 == p2);
    }
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::Parity>::value);

  SECTION("Even.") {
    for (auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      auto p1 = imsrg::Parity::Even();
      p2 = std::move(p1);

      REQUIRE(p2.IsEven());
    }
  }

  SECTION("Odd.") {
    for (auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      auto p1 = imsrg::Parity::Odd();
      p2 = std::move(p1);

      REQUIRE(p2.IsOdd());
    }
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::Parity>::value);
}

TEST_CASE("Test member swap") {
  REQUIRE(std::is_nothrow_swappable<imsrg::Parity>::value);

  for (const auto p1 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
    for (const auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      auto p1_copy = p1;
      auto p2_copy = p2;

      REQUIRE(p1_copy == p1);
      REQUIRE(p2_copy == p2);

      p1_copy.swap(p2_copy);

      REQUIRE(p1_copy == p2);
      REQUIRE(p2_copy == p1);
    }
  }
}

TEST_CASE("Test nonmember swap") {
  REQUIRE(std::is_nothrow_swappable<imsrg::Parity>::value);
  using std::swap;

  for (const auto p1 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
    for (const auto p2 : {imsrg::Parity::Even(), imsrg::Parity::Odd()}) {
      auto p1_copy = p1;
      auto p2_copy = p2;

      REQUIRE(p1_copy == p1);
      REQUIRE(p2_copy == p2);

      swap(p1_copy, p2_copy);

      REQUIRE(p1_copy == p2);
      REQUIRE(p2_copy == p1);
    }
  }
}

TEST_CASE("Test <.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 < p2) == (i1 < i2));
    }
  }
}

TEST_CASE("Test <=.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 <= p2) == (i1 <= i2));
    }
  }
}

TEST_CASE("Test ==.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 == p2) == (i1 == i2));
    }
  }
}

TEST_CASE("Test >.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 > p2) == (i1 > i2));
    }
  }
}

TEST_CASE("Test !=.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 != p2) == (i1 != i2));
    }
  }
}

TEST_CASE("Test >=.") {
  std::array<imsrg::Parity, 2> ps = {imsrg::Parity::Even(),
                                     imsrg::Parity::Odd()};

  for (const auto i1 : {0, 1}) {
    const auto p1 = ps[i1];
    for (const auto i2 : {0, 1}) {
      const auto p2 = ps[i2];
      REQUIRE((p1 >= p2) == (i1 >= i2));
    }
  }
}

TEST_CASE("Test addition rules.") {
  using imsrg::Parity;
  REQUIRE(Parity::Odd() + Parity::Odd() == Parity::Even());
  REQUIRE(Parity::Even() + Parity::Odd() == Parity::Odd());
  REQUIRE(Parity::Odd() + Parity::Even() == Parity::Odd());
  REQUIRE(Parity::Even() + Parity::Even() == Parity::Even());
}

TEST_CASE("Test subtraction rules.") {
  using imsrg::Parity;
  REQUIRE(Parity::Odd() - Parity::Odd() == Parity::Even());
  REQUIRE(Parity::Even() - Parity::Odd() == Parity::Odd());
  REQUIRE(Parity::Odd() - Parity::Even() == Parity::Odd());
  REQUIRE(Parity::Even() - Parity::Even() == Parity::Even());
}
