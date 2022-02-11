// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/channel_key.h"

#include <vector>

#include "absl/hash/hash_testing.h"

#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

static std::vector<imsrg::TotalAngMom> ValidJJs() {
  return {
      imsrg::TotalAngMom(1),  imsrg::TotalAngMom(3),  imsrg::TotalAngMom(5),
      imsrg::TotalAngMom(7),  imsrg::TotalAngMom(9),  imsrg::TotalAngMom(11),
      imsrg::TotalAngMom(13), imsrg::TotalAngMom(15), imsrg::TotalAngMom(17),
      imsrg::TotalAngMom(19), imsrg::TotalAngMom(21)};
}

static std::vector<imsrg::IsospinProj> ValidM_TTs() {
  return {imsrg::IsospinProj::Neutron(), imsrg::IsospinProj::Proton()};
}

static std::vector<imsrg::Parity> ValidPs() {
  return {imsrg::Parity::Even(), imsrg::Parity::Odd()};
}

static std::vector<imsrg::JJ_P_M_TT> ValidJJPMTTs() {
  std::vector<imsrg::JJ_P_M_TT> valid;
  for (const auto jj : ValidJJs()) {
    for (const auto p : ValidPs()) {
      for (const auto m_tt : ValidM_TTs()) {
        valid.push_back(imsrg::JJ_P_M_TT(jj, p, m_tt));
      }
    }
  }
  return valid;
}

TEST_CASE("Test jj, p, m_tt ctor and JJ(), P(), M_TT().") {
  for (const auto jj : ValidJJs()) {
    for (const auto p : ValidPs()) {
      for (const auto m_tt : ValidM_TTs()) {
        imsrg::SPChannelKey chankey(jj, p, m_tt);
        REQUIRE(chankey.JJ() == jj);
        REQUIRE(chankey.P() == p);
        REQUIRE(chankey.M_TT() == m_tt);
      }
    }
  }
}

TEST_CASE("Test indirect jjpmtt ctor and JJ(), P(), M_TT().") {
  for (const auto jjpmtt : ValidJJPMTTs()) {
    imsrg::SPChannelKey chankey(jjpmtt);
    REQUIRE(chankey.JJ() == jjpmtt.JJ());
    REQUIRE(chankey.P() == jjpmtt.P());
    REQUIRE(chankey.M_TT() == jjpmtt.M_TT());
  }
}

TEST_CASE("Test standard ctor fails with jj=0.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(0);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with jj=2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(2);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with jj=4.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(4);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with jj=0.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(0);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with jj=2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(2);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with jj=4.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(4);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj::Neutron();

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with m_tt=-2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(-2);

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with m_tt=0.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(0);

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with m_tt=2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(2);

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test standard ctor fails with m_tt=4.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(4);

  imsrg::SPChannelKey chankey(jj, p, m_tt);

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with m_tt=-2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(-2);

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with m_tt=0.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(0);

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with m_tt=2.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(2);

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test indirect ctor fails with m_tt=4.", "[!hide][!shouldfail]") {
  imsrg::TotalAngMom jj(1);
  auto p = imsrg::Parity::Odd();
  auto m_tt = imsrg::IsospinProj(4);

  imsrg::SPChannelKey chankey(imsrg::JJ_P_M_TT(jj, p, m_tt));

  REQUIRE(chankey.JJ() == jj);
  REQUIRE(chankey.P() == p);
  REQUIRE(chankey.M_TT() == m_tt);
}

TEST_CASE("Test for no overflow in index computation.") {
  int max_jj_i = 99;
  std::size_t max_index = 4 * 99 + 3;

  for (int jj_i = 1; jj_i <= max_jj_i; jj_i += 2) {
    const imsrg::TotalAngMom jj(jj_i);
    for (const auto p : ValidPs()) {
      for (const auto m_tt : ValidM_TTs()) {
        imsrg::SPChannelKey chankey(jj, p, m_tt);

        REQUIRE(chankey.Index() <= max_index);
      }
    }
  }
}

TEST_CASE("Test index is unique.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1.Index() == chankey2.Index()) ==
                      ((jj1 == jj2) && (p1 == p2) && (m_tt1 == m_tt2)));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::SPChannelKey>::value);
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::SPChannelKey>::value);
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::SPChannelKey>::value);
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::SPChannelKey>::value);
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::SPChannelKey>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::SPChannelKey>::value);

  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE(chankey1.JJ() == jj1);
              REQUIRE(chankey1.P() == p1);
              REQUIRE(chankey1.M_TT() == m_tt1);
              REQUIRE(chankey2.JJ() == jj2);
              REQUIRE(chankey2.P() == p2);
              REQUIRE(chankey2.M_TT() == m_tt2);

              const auto index1 = chankey1.Index();
              const auto index2 = chankey2.Index();

              chankey1.swap(chankey2);

              REQUIRE(chankey1.JJ() == jj2);
              REQUIRE(chankey1.P() == p2);
              REQUIRE(chankey1.M_TT() == m_tt2);
              REQUIRE(chankey1.Index() == index2);
              REQUIRE(chankey2.JJ() == jj1);
              REQUIRE(chankey2.P() == p1);
              REQUIRE(chankey2.M_TT() == m_tt1);
              REQUIRE(chankey2.Index() == index1);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPChannelKey>::value);

  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE(chankey1.JJ() == jj1);
              REQUIRE(chankey1.P() == p1);
              REQUIRE(chankey1.M_TT() == m_tt1);
              REQUIRE(chankey2.JJ() == jj2);
              REQUIRE(chankey2.P() == p2);
              REQUIRE(chankey2.M_TT() == m_tt2);

              const auto index1 = chankey1.Index();
              const auto index2 = chankey2.Index();

              swap(chankey1, chankey2);

              REQUIRE(chankey1.JJ() == jj2);
              REQUIRE(chankey1.P() == p2);
              REQUIRE(chankey1.M_TT() == m_tt2);
              REQUIRE(chankey1.Index() == index2);
              REQUIRE(chankey2.JJ() == jj1);
              REQUIRE(chankey2.P() == p1);
              REQUIRE(chankey2.M_TT() == m_tt1);
              REQUIRE(chankey2.Index() == index1);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test ==.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 == chankey2) ==
                      ((jj1 == jj2) && (p1 == p2) && (m_tt1 == m_tt2)));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test !=.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 != chankey2) ==
                      !((jj1 == jj2) && (p1 == p2) && (m_tt1 == m_tt2)));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test <.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 < chankey2) ==
                      (chankey1.Index() < chankey2.Index()));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test <=.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 <= chankey2) ==
                      (chankey1.Index() <= chankey2.Index()));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test >.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 > chankey2) ==
                      (chankey1.Index() > chankey2.Index()));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test >=.") {
  for (const auto jj1 : ValidJJs()) {
    for (const auto jj2 : ValidJJs()) {
      for (const auto p1 : ValidPs()) {
        for (const auto p2 : ValidPs()) {
          for (const auto m_tt1 : ValidM_TTs()) {
            for (const auto m_tt2 : ValidM_TTs()) {
              imsrg::SPChannelKey chankey1(jj1, p1, m_tt1);
              imsrg::SPChannelKey chankey2(jj2, p2, m_tt2);

              REQUIRE((chankey1 >= chankey2) ==
                      (chankey1.Index() >= chankey2.Index()));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test proper abseil hash.") {
  std::vector<imsrg::SPChannelKey> chankeys;
  for (const auto jjpmtt : ValidJJPMTTs()) {
    chankeys.push_back(imsrg::SPChannelKey(jjpmtt));
  }
  REQUIRE(absl::VerifyTypeImplementsAbslHashCorrectly(chankeys));
}
