// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/isospin_projection.h"

#include <cmath>
#include <type_traits>
#include <utility>

#include "imsrg/quantum_numbers/coupling/m_jj.h"

#include "tests/catch.hpp"

TEST_CASE("Test int constructor and AsInt().") {
  for (const auto& m_tt : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::IsospinProj m_tt_o(m_tt);

    REQUIRE(m_tt_o.AsInt() == m_tt);
  }
}

TEST_CASE("Test M_JJ constructor and AsM_JJ().") {
  for (const auto& m_jj : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::M_JJ m_jj_o(m_jj);

    imsrg::IsospinProj m_tt(m_jj_o);

    REQUIRE(m_tt.AsM_JJ() == m_jj_o);
  }
}

TEST_CASE("Test proton and neutron.") {
  auto p = imsrg::IsospinProj::Proton();
  auto n = imsrg::IsospinProj::Neutron();

  REQUIRE(n != p);
  REQUIRE(p + n == imsrg::IsospinProj(0));
  REQUIRE(std::abs(p.AsInt()) == 1);
  REQUIRE(std::abs(n.AsInt()) == 1);
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::IsospinProj>::value);

  for (const auto& m_tt : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::IsospinProj m_tt1(m_tt);
    imsrg::IsospinProj m_tt2(m_tt1);

    REQUIRE(m_tt1 == m_tt2);
    REQUIRE(m_tt1.AsInt() == m_tt);
    REQUIRE(m_tt2.AsInt() == m_tt);
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::IsospinProj>::value);

  for (const auto& m_tt : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::IsospinProj m_tt1(m_tt);
    imsrg::IsospinProj m_tt2(std::move(m_tt1));

    REQUIRE(m_tt2.AsInt() == m_tt);
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::IsospinProj>::value);

  for (const auto& m_tt : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::IsospinProj m_tt1(m_tt);
    imsrg::IsospinProj m_tt2(0);

    m_tt2 = m_tt1;

    REQUIRE(m_tt1 == m_tt2);
    REQUIRE(m_tt1.AsInt() == m_tt);
    REQUIRE(m_tt2.AsInt() == m_tt);
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::IsospinProj>::value);

  for (const auto& m_tt : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    imsrg::IsospinProj m_tt1(m_tt);
    imsrg::IsospinProj m_tt2(0);

    m_tt2 = std::move(m_tt1);

    REQUIRE(m_tt2.AsInt() == m_tt);
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::IsospinProj>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::IsospinProj>::value);

  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE(m_tt1.AsInt() == x1);
      REQUIRE(m_tt2.AsInt() == x2);

      m_tt1.swap(m_tt2);

      REQUIRE(m_tt1.AsInt() == x2);
      REQUIRE(m_tt2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::IsospinProj>::value);

  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE(m_tt1.AsInt() == x1);
      REQUIRE(m_tt2.AsInt() == x2);

      swap(m_tt1, m_tt2);

      REQUIRE(m_tt1.AsInt() == x2);
      REQUIRE(m_tt2.AsInt() == x1);
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 < m_tt2) == (x1 < x2));
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 <= m_tt2) == (x1 <= x2));
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 == m_tt2) == (x1 == x2));
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 > m_tt2) == (x1 > x2));
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 != m_tt2) == (x1 != x2));
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE((m_tt1 >= m_tt2) == (x1 >= x2));
    }
  }
}

TEST_CASE("Test operator+.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE(m_tt1.AsInt() == x1);
      REQUIRE(m_tt2.AsInt() == x2);

      auto m_tt3 = m_tt1 + m_tt2;

      REQUIRE(m_tt3.AsInt() == x1 + x2);
    }
  }
}

TEST_CASE("Test operator-.") {
  for (const auto& x1 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    for (const auto& x2 : {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      imsrg::IsospinProj m_tt1(x1);
      imsrg::IsospinProj m_tt2(x2);

      REQUIRE(m_tt1.AsInt() == x1);
      REQUIRE(m_tt2.AsInt() == x2);

      auto m_tt3 = m_tt1 - m_tt2;
      auto m_tt4 = m_tt2 - m_tt1;

      REQUIRE(m_tt3.AsInt() == x1 - x2);
      REQUIRE(m_tt4.AsInt() == x2 - x1);
    }
  }
}
