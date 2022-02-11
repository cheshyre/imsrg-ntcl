// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/state.h"

#include <type_traits>
#include <utility>
#include <vector>

#include "imsrg/model_space/jj_p_m_tt.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/occupation_number.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/spin.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

using imsrg::HOEnergy;
using imsrg::IsospinProj;
using imsrg::JJ_P_M_TT;
using imsrg::OccupationNumber;
using imsrg::OrbitalAngMom;
using imsrg::RadialExcitationNumber;
using imsrg::Spin;
using imsrg::TotalAngMom;

TEST_CASE("Test full constructor and RadialN().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.RadialN() == n_rad);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and RadialN().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.RadialN() == n_rad);
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.RadialN() == n_rad);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and L().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.L() == l);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and L().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.L() == l);
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.L() == l);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and JJ().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.JJ() == jj);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and JJ().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.JJ() == jj);
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.JJ() == jj);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and M_TT().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.M_TT() == m_tt);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and M_TT().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.M_TT() == m_tt);
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.M_TT() == m_tt);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and OccupationN().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.OccupationN() == n_occ);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor, SetOccupationN(), and OccupationN().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.OccupationN() == OccupationNumber(0.0));
            for (const auto& n_occ :
                 {OccupationNumber(1.0 / 8), OccupationNumber(1.0 / 6),
                  OccupationNumber(1.0 / 4), OccupationNumber(1.0 / 2),
                  OccupationNumber(1.0), OccupationNumber(0.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.OccupationN() == n_occ);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and E().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.E() == HOEnergy(n_rad, l));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and E().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.E() == HOEnergy(n_rad, l));
            for (const auto& n_occ :
                 {OccupationNumber(1.0 / 8), OccupationNumber(1.0 / 6),
                  OccupationNumber(1.0 / 4), OccupationNumber(1.0 / 2),
                  OccupationNumber(1.0), OccupationNumber(0.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.E() == HOEnergy(n_rad, l));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test full constructor and GetJJ_P_M_TT().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            for (const auto& n_occ :
                 {OccupationNumber(0.0), OccupationNumber(1.0 / 8),
                  OccupationNumber(1.0 / 6), OccupationNumber(1.0 / 4),
                  OccupationNumber(1.0 / 2), OccupationNumber(1.0)}) {
              imsrg::SPState state(n_rad, l, jj, m_tt, n_occ);

              REQUIRE(state.GetJJ_P_M_TT() == JJ_P_M_TT(jj, l.Parity(), m_tt));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test reduced constructor and GetJJ_P_M_TT().") {
  for (const auto& n_rad :
       {RadialExcitationNumber(0), RadialExcitationNumber(1),
        RadialExcitationNumber(2), RadialExcitationNumber(3)}) {
    for (const auto& l : {OrbitalAngMom(0), OrbitalAngMom(1), OrbitalAngMom(2),
                          OrbitalAngMom(3)}) {
      // Can consider explicit support for other spins (for example, 3/2)
      for (const auto& s : {Spin::OneHalf()}) {
        for (const auto& jj : imsrg::GenerateCouplingRange<TotalAngMom>(l, s)) {
          for (const auto& m_tt : {
                   IsospinProj(-2),
                   IsospinProj(-1),
                   IsospinProj(0),
                   IsospinProj(1),
                   IsospinProj(2),
               }) {
            imsrg::SPState state(n_rad, l, jj, m_tt);
            REQUIRE(state.GetJJ_P_M_TT() == JJ_P_M_TT(jj, l.Parity(), m_tt));
            for (const auto& n_occ :
                 {OccupationNumber(1.0 / 8), OccupationNumber(1.0 / 6),
                  OccupationNumber(1.0 / 4), OccupationNumber(1.0 / 2),
                  OccupationNumber(1.0), OccupationNumber(0.0)}) {
              state.SetOccupationN(n_occ);

              REQUIRE(state.GetJJ_P_M_TT() == JJ_P_M_TT(jj, l.Parity(), m_tt));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    imsrg::SPState state2(state);

    REQUIRE(state == state2);
    REQUIRE(state.RadialN() == state2.RadialN());
    REQUIRE(state.L() == state2.L());
    REQUIRE(state.JJ() == state2.JJ());
    REQUIRE(state.M_TT() == state2.M_TT());
    REQUIRE(state.OccupationN() == state2.OccupationN());
  }
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    imsrg::SPState state2(state);
    imsrg::SPState state3(std::move(state));

    REQUIRE(state == state3);
    REQUIRE(state.RadialN() == state3.RadialN());
    REQUIRE(state.L() == state3.L());
    REQUIRE(state.JJ() == state3.JJ());
    REQUIRE(state.M_TT() == state3.M_TT());
    REQUIRE(state.OccupationN() == state3.OccupationN());
  }
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    imsrg::SPState state2(RadialExcitationNumber(0), OrbitalAngMom(0),
                          TotalAngMom(1), IsospinProj::Proton(),
                          OccupationNumber::Hole());
    state2 = state;

    REQUIRE(state == state2);
    REQUIRE(state.RadialN() == state2.RadialN());
    REQUIRE(state.L() == state2.L());
    REQUIRE(state.JJ() == state2.JJ());
    REQUIRE(state.M_TT() == state2.M_TT());
    REQUIRE(state.OccupationN() == state2.OccupationN());
  }
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    imsrg::SPState state2(state);
    imsrg::SPState state3(RadialExcitationNumber(0), OrbitalAngMom(0),
                          TotalAngMom(1), IsospinProj::Proton(),
                          OccupationNumber::Hole());
    state3 = std::move(state2);

    REQUIRE(state == state3);
    REQUIRE(state.RadialN() == state3.RadialN());
    REQUIRE(state.L() == state3.L());
    REQUIRE(state.JJ() == state3.JJ());
    REQUIRE(state.M_TT() == state3.M_TT());
    REQUIRE(state.OccupationN() == state3.OccupationN());
  }
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::SPState>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state1 :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    for (const auto& state2 :
         {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
      imsrg::SPState s1(state1);
      imsrg::SPState s2(state2);

      REQUIRE(s1 == state1);
      REQUIRE(s2 == state2);

      s1.swap(s2);

      REQUIRE(s1 == state2);
      REQUIRE(s2 == state1);
    }
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPState>::value);

  const imsrg::SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  const imsrg::SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                                  TotalAngMom(5), IsospinProj::Proton(),
                                  OccupationNumber::Particle());

  const imsrg::SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Neutron(),
                                  OccupationNumber::Hole());

  const imsrg::SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                                  TotalAngMom(7), IsospinProj::Neutron(),
                                  OccupationNumber::Particle());

  for (const auto& state1 :
       {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
    for (const auto& state2 :
         {p_0s1_hole, p_0d5_hole, p_2d5_part, n_0p1_hole, n_3f7_part}) {
      imsrg::SPState s1(state1);
      imsrg::SPState s2(state2);

      REQUIRE(s1 == state1);
      REQUIRE(s2 == state2);

      swap(s1, s2);

      REQUIRE(s1 == state2);
      REQUIRE(s2 == state1);
    }
  }
}

TEST_CASE("Test == (0p1/2 proton vs variations).") {
  const imsrg::SPState p_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  REQUIRE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(1), TotalAngMom(1),
                                       IsospinProj::Proton(),
                                       OccupationNumber::Hole()));

  // The following checks vary each input individually.
  // The resulting states should not be equal.

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(1),
                                             OrbitalAngMom(1), TotalAngMom(1),
                                             IsospinProj::Proton(),
                                             OccupationNumber::Hole()));

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(0), TotalAngMom(1),
                                             IsospinProj::Proton(),
                                             OccupationNumber::Hole()));

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(1), TotalAngMom(3),
                                             IsospinProj::Proton(),
                                             OccupationNumber::Hole()));

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(1), TotalAngMom(1),
                                             IsospinProj::Neutron(),
                                             OccupationNumber::Hole()));

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(1), TotalAngMom(1),
                                             IsospinProj::Proton(),
                                             OccupationNumber::Particle()));

  REQUIRE_FALSE(p_0p1_hole == imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(1), TotalAngMom(1),
                                             IsospinProj::Proton(),
                                             OccupationNumber(0.5)));
}

TEST_CASE("Test != (0p1/2 proton vs variations).") {
  const imsrg::SPState p_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                                  TotalAngMom(1), IsospinProj::Proton(),
                                  OccupationNumber::Hole());

  REQUIRE_FALSE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                             OrbitalAngMom(1), TotalAngMom(1),
                                             IsospinProj::Proton(),
                                             OccupationNumber::Hole()));

  // The following checks vary each input individually.
  // The resulting states should not be equal.

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(1),
                                       OrbitalAngMom(1), TotalAngMom(1),
                                       IsospinProj::Proton(),
                                       OccupationNumber::Hole()));

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(0), TotalAngMom(1),
                                       IsospinProj::Proton(),
                                       OccupationNumber::Hole()));

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(1), TotalAngMom(3),
                                       IsospinProj::Proton(),
                                       OccupationNumber::Hole()));

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(1), TotalAngMom(1),
                                       IsospinProj::Neutron(),
                                       OccupationNumber::Hole()));

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(1), TotalAngMom(1),
                                       IsospinProj::Proton(),
                                       OccupationNumber::Particle()));

  REQUIRE(p_0p1_hole != imsrg::SPState(RadialExcitationNumber(0),
                                       OrbitalAngMom(1), TotalAngMom(1),
                                       IsospinProj::Proton(),
                                       OccupationNumber(0.5)));
}
