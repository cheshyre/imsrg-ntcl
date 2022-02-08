// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/jj_p_m_tt.h"

#include <type_traits>
#include <utility>

#include "absl/hash/hash_testing.h"

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

using imsrg::IsospinProj;
using imsrg::Parity;
using imsrg::TotalAngMom;

TEST_CASE("Test constructor and JJ().") {
  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt(jj, p, m_tt);

        REQUIRE(jjpmtt.JJ() == jj);
      }
    }
  }
}

TEST_CASE("Test constructor and P().") {
  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt(jj, p, m_tt);

        REQUIRE(jjpmtt.P() == p);
      }
    }
  }
}

TEST_CASE("Test constructor and M_TT().") {
  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt(jj, p, m_tt);

        REQUIRE(jjpmtt.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj, p, m_tt);
        imsrg::JJ_P_M_TT jjpmtt2(jjpmtt1);

        REQUIRE(jjpmtt1.JJ() == jj);
        REQUIRE(jjpmtt1.P() == p);
        REQUIRE(jjpmtt1.M_TT() == m_tt);
        REQUIRE(jjpmtt2.JJ() == jj);
        REQUIRE(jjpmtt2.P() == p);
        REQUIRE(jjpmtt2.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj, p, m_tt);
        imsrg::JJ_P_M_TT jjpmtt2(std::move(jjpmtt1));

        REQUIRE(jjpmtt2.JJ() == jj);
        REQUIRE(jjpmtt2.P() == p);
        REQUIRE(jjpmtt2.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj, p, m_tt);
        imsrg::JJ_P_M_TT jjpmtt2(TotalAngMom(0), Parity::Even(),
                                 IsospinProj(0));

        jjpmtt2 = jjpmtt1;

        REQUIRE(jjpmtt1.JJ() == jj);
        REQUIRE(jjpmtt1.P() == p);
        REQUIRE(jjpmtt1.M_TT() == m_tt);
        REQUIRE(jjpmtt2.JJ() == jj);
        REQUIRE(jjpmtt2.P() == p);
        REQUIRE(jjpmtt2.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                         TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj, p, m_tt);
        imsrg::JJ_P_M_TT jjpmtt2(TotalAngMom(0), Parity::Even(),
                                 IsospinProj(0));

        jjpmtt2 = std::move(jjpmtt1);

        REQUIRE(jjpmtt2.JJ() == jj);
        REQUIRE(jjpmtt2.P() == p);
        REQUIRE(jjpmtt2.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::JJ_P_M_TT>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj1 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                          TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p1 : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt1 : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        for (const auto& jj2 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                                TotalAngMom(3), TotalAngMom(4)}) {
          for (const auto& p2 : {Parity::Even(), Parity::Odd()}) {
            for (const auto& m_tt2 : {
                     IsospinProj(-2),
                     IsospinProj(-1),
                     IsospinProj(0),
                     IsospinProj(1),
                     IsospinProj(2),
                 }) {
              imsrg::JJ_P_M_TT jjpmtt1(jj1, p1, m_tt1);
              imsrg::JJ_P_M_TT jjpmtt2(jj2, p2, m_tt2);
              REQUIRE(jjpmtt1.JJ() == jj1);
              REQUIRE(jjpmtt1.P() == p1);
              REQUIRE(jjpmtt1.M_TT() == m_tt1);
              REQUIRE(jjpmtt2.JJ() == jj2);
              REQUIRE(jjpmtt2.P() == p2);
              REQUIRE(jjpmtt2.M_TT() == m_tt2);

              jjpmtt1.swap(jjpmtt2);

              REQUIRE(jjpmtt2.JJ() == jj1);
              REQUIRE(jjpmtt2.P() == p1);
              REQUIRE(jjpmtt2.M_TT() == m_tt1);
              REQUIRE(jjpmtt1.JJ() == jj2);
              REQUIRE(jjpmtt1.P() == p2);
              REQUIRE(jjpmtt1.M_TT() == m_tt2);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::JJ_P_M_TT>::value);

  for (const auto& jj1 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                          TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p1 : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt1 : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        for (const auto& jj2 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                                TotalAngMom(3), TotalAngMom(4)}) {
          for (const auto& p2 : {Parity::Even(), Parity::Odd()}) {
            for (const auto& m_tt2 : {
                     IsospinProj(-2),
                     IsospinProj(-1),
                     IsospinProj(0),
                     IsospinProj(1),
                     IsospinProj(2),
                 }) {
              imsrg::JJ_P_M_TT jjpmtt1(jj1, p1, m_tt1);
              imsrg::JJ_P_M_TT jjpmtt2(jj2, p2, m_tt2);
              REQUIRE(jjpmtt1.JJ() == jj1);
              REQUIRE(jjpmtt1.P() == p1);
              REQUIRE(jjpmtt1.M_TT() == m_tt1);
              REQUIRE(jjpmtt2.JJ() == jj2);
              REQUIRE(jjpmtt2.P() == p2);
              REQUIRE(jjpmtt2.M_TT() == m_tt2);

              swap(jjpmtt1, jjpmtt2);

              REQUIRE(jjpmtt2.JJ() == jj1);
              REQUIRE(jjpmtt2.P() == p1);
              REQUIRE(jjpmtt2.M_TT() == m_tt1);
              REQUIRE(jjpmtt1.JJ() == jj2);
              REQUIRE(jjpmtt1.P() == p2);
              REQUIRE(jjpmtt1.M_TT() == m_tt2);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto& jj1 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                          TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p1 : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt1 : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj1, p1, m_tt1);
        for (const auto& jj2 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                                TotalAngMom(3), TotalAngMom(4)}) {
          for (const auto& p2 : {Parity::Even(), Parity::Odd()}) {
            for (const auto& m_tt2 : {
                     IsospinProj(-2),
                     IsospinProj(-1),
                     IsospinProj(0),
                     IsospinProj(1),
                     IsospinProj(2),
                 }) {
              imsrg::JJ_P_M_TT jjpmtt2(jj2, p2, m_tt2);

              bool expect = (jj1 == jj2) && (p1 == p2) && (m_tt1 == m_tt2);

              REQUIRE((jjpmtt1 == jjpmtt2) == expect);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto& jj1 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                          TotalAngMom(3), TotalAngMom(4)}) {
    for (const auto& p1 : {Parity::Even(), Parity::Odd()}) {
      for (const auto& m_tt1 : {
               IsospinProj(-2),
               IsospinProj(-1),
               IsospinProj(0),
               IsospinProj(1),
               IsospinProj(2),
           }) {
        imsrg::JJ_P_M_TT jjpmtt1(jj1, p1, m_tt1);
        for (const auto& jj2 : {TotalAngMom(0), TotalAngMom(1), TotalAngMom(2),
                                TotalAngMom(3), TotalAngMom(4)}) {
          for (const auto& p2 : {Parity::Even(), Parity::Odd()}) {
            for (const auto& m_tt2 : {
                     IsospinProj(-2),
                     IsospinProj(-1),
                     IsospinProj(0),
                     IsospinProj(1),
                     IsospinProj(2),
                 }) {
              imsrg::JJ_P_M_TT jjpmtt2(jj2, p2, m_tt2);

              bool expect = !((jj1 == jj2) && (p1 == p2) && (m_tt1 == m_tt2));

              REQUIRE((jjpmtt1 != jjpmtt2) == expect);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test proper abseil hash.") {
  using imsrg::JJ_P_M_TT;
  REQUIRE(absl::VerifyTypeImplementsAbslHashCorrectly(
      {JJ_P_M_TT(TotalAngMom(0), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(0), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(0), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(0), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(0), Parity::Even(), IsospinProj(2)),
       JJ_P_M_TT(TotalAngMom(1), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(1), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(1), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(1), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(1), Parity::Even(), IsospinProj(2)),
       JJ_P_M_TT(TotalAngMom(2), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(2), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(2), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(2), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(2), Parity::Even(), IsospinProj(2)),
       JJ_P_M_TT(TotalAngMom(3), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(3), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(3), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(3), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(3), Parity::Even(), IsospinProj(2)),
       JJ_P_M_TT(TotalAngMom(4), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(4), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(4), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(4), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(4), Parity::Even(), IsospinProj(2)),
       JJ_P_M_TT(TotalAngMom(5), Parity::Even(), IsospinProj(-2)),
       JJ_P_M_TT(TotalAngMom(5), Parity::Even(), IsospinProj(-1)),
       JJ_P_M_TT(TotalAngMom(5), Parity::Even(), IsospinProj(0)),
       JJ_P_M_TT(TotalAngMom(5), Parity::Even(), IsospinProj(1)),
       JJ_P_M_TT(TotalAngMom(5), Parity::Even(), IsospinProj(2))}));
}
