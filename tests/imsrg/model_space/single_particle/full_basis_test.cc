// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/full_basis.h"

#include <vector>

#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/occupation_number.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

static bool IsStateInBasis(imsrg::SPState s, const imsrg::SPFullBasis& basis) {
  for (std::size_t i = 0; i < basis.size(); i++) {
    if (basis.at(i) == s) {
      return true;
    }
  }
  return false;
}

TEST_CASE(
    "Test construction of simple 2-state basis and test membership and size.") {
  using imsrg::IsospinProj;
  using imsrg::OccupationNumber;
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  const SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                           TotalAngMom(1), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Particle());

  const SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                           TotalAngMom(1), IsospinProj::Neutron(),
                           OccupationNumber::Hole());

  const SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                           TotalAngMom(7), IsospinProj::Neutron(),
                           OccupationNumber::Particle());

  std::vector<SPState> states = {p_0s1_hole, n_0p1_hole};

  imsrg::SPFullBasis basis(states);

  REQUIRE(basis.size() == 2);

  REQUIRE(IsStateInBasis(p_0s1_hole, basis));
  REQUIRE(IsStateInBasis(n_0p1_hole, basis));
  REQUIRE_FALSE(IsStateInBasis(n_3f7_part, basis));
  REQUIRE_FALSE(IsStateInBasis(p_2d5_part, basis));
  REQUIRE_FALSE(IsStateInBasis(p_0d5_hole, basis));
}

TEST_CASE("Test copy contructor.") {
  REQUIRE(std::is_copy_constructible<imsrg::SPFullBasis>::value);
}

TEST_CASE("Test move contructor.") {
  REQUIRE(std::is_nothrow_move_constructible<imsrg::SPFullBasis>::value);
}

TEST_CASE("Test copy assignment.") {
  REQUIRE(std::is_copy_assignable<imsrg::SPFullBasis>::value);
}

TEST_CASE("Test move assignment.") {
  REQUIRE(std::is_nothrow_move_assignable<imsrg::SPFullBasis>::value);
}

TEST_CASE("Test destructor.") {
  REQUIRE(std::is_nothrow_destructible<imsrg::SPFullBasis>::value);
}

TEST_CASE("Test member swap.") {
  REQUIRE(std::is_nothrow_swappable<imsrg::SPFullBasis>::value);

  using imsrg::IsospinProj;
  using imsrg::OccupationNumber;
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  const SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                           TotalAngMom(1), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Particle());

  const SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                           TotalAngMom(1), IsospinProj::Neutron(),
                           OccupationNumber::Hole());

  const SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                           TotalAngMom(7), IsospinProj::Neutron(),
                           OccupationNumber::Particle());

  std::vector<SPState> states1 = {p_0s1_hole, n_0p1_hole};
  std::vector<SPState> states2 = {p_0d5_hole, p_2d5_part, n_3f7_part};

  imsrg::SPFullBasis basis1(states1);
  imsrg::SPFullBasis basis2(states2);

  REQUIRE(basis1.size() == states1.size());
  REQUIRE(basis2.size() == states2.size());
  for (const auto& a : states1) {
    REQUIRE(IsStateInBasis(a, basis1));
  }
  for (const auto& a : states2) {
    REQUIRE(IsStateInBasis(a, basis2));
  }

  basis1.swap(basis2);

  REQUIRE(basis1.size() == states2.size());
  REQUIRE(basis2.size() == states1.size());
  for (const auto& a : states2) {
    REQUIRE(IsStateInBasis(a, basis1));
  }
  for (const auto& a : states1) {
    REQUIRE(IsStateInBasis(a, basis2));
  }
}

TEST_CASE("Test nonmember swap.") {
  using std::swap;
  REQUIRE(std::is_nothrow_swappable<imsrg::SPFullBasis>::value);

  using imsrg::IsospinProj;
  using imsrg::OccupationNumber;
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  const SPState p_0s1_hole(RadialExcitationNumber(0), OrbitalAngMom(0),
                           TotalAngMom(1), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_0d5_hole(RadialExcitationNumber(0), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Hole());

  const SPState p_2d5_part(RadialExcitationNumber(2), OrbitalAngMom(2),
                           TotalAngMom(5), IsospinProj::Proton(),
                           OccupationNumber::Particle());

  const SPState n_0p1_hole(RadialExcitationNumber(0), OrbitalAngMom(1),
                           TotalAngMom(1), IsospinProj::Neutron(),
                           OccupationNumber::Hole());

  const SPState n_3f7_part(RadialExcitationNumber(3), OrbitalAngMom(3),
                           TotalAngMom(7), IsospinProj::Neutron(),
                           OccupationNumber::Particle());

  std::vector<SPState> states1 = {p_0s1_hole, n_0p1_hole};
  std::vector<SPState> states2 = {p_0d5_hole, p_2d5_part, n_3f7_part};

  imsrg::SPFullBasis basis1(states1);
  imsrg::SPFullBasis basis2(states2);

  REQUIRE(basis1.size() == states1.size());
  REQUIRE(basis2.size() == states2.size());
  for (const auto& a : states1) {
    REQUIRE(IsStateInBasis(a, basis1));
  }
  for (const auto& a : states2) {
    REQUIRE(IsStateInBasis(a, basis2));
  }

  swap(basis1, basis2);

  REQUIRE(basis1.size() == states2.size());
  REQUIRE(basis2.size() == states1.size());
  for (const auto& a : states2) {
    REQUIRE(IsStateInBasis(a, basis1));
  }
  for (const auto& a : states1) {
    REQUIRE(IsStateInBasis(a, basis2));
  }
}

TEST_CASE("Test FromEMax factory method (no occs, emax=2).") {
  using imsrg::HOEnergy;
  using imsrg::IsospinProj;
  using imsrg::OccupationNumber;
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  HOEnergy emax(2);

  std::vector<SPState> sampled_emax2_states = {
      SPState(RadialExcitationNumber(0), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(1), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(1), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(2), TotalAngMom(3),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(2), TotalAngMom(3),
              IsospinProj::Neutron(), OccupationNumber::Particle())};

  std::vector<SPState> sampled_non_emax2_states = {
      SPState(RadialExcitationNumber(2), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(2), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(2), OrbitalAngMom(5), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(2), OrbitalAngMom(5), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle())};

  auto basis = imsrg::SPFullBasis::FromEMax(emax);

  REQUIRE(basis.size() == 12);

  for (const auto& x : sampled_emax2_states) {
    REQUIRE(IsStateInBasis(x, basis));
  }

  for (const auto& x : sampled_non_emax2_states) {
    REQUIRE_FALSE(IsStateInBasis(x, basis));
  }
}

TEST_CASE("Test FromEMax factory method (no occs, emax=4).") {
  using imsrg::HOEnergy;
  using imsrg::IsospinProj;
  using imsrg::OccupationNumber;
  using imsrg::OrbitalAngMom;
  using imsrg::RadialExcitationNumber;
  using imsrg::SPState;
  using imsrg::TotalAngMom;

  HOEnergy emax(4);

  std::vector<SPState> sampled_emax2_states = {
      SPState(RadialExcitationNumber(0), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(1), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(1), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(2), TotalAngMom(3),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(0), OrbitalAngMom(2), TotalAngMom(3),
              IsospinProj::Neutron(), OccupationNumber::Particle())};

  std::vector<SPState> sampled_emax4_states = {
      SPState(RadialExcitationNumber(2), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(2), OrbitalAngMom(0), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle())};

  std::vector<SPState> sampled_non_emax4_states = {
      SPState(RadialExcitationNumber(2), OrbitalAngMom(5), TotalAngMom(1),
              IsospinProj::Proton(), OccupationNumber::Particle()),
      SPState(RadialExcitationNumber(2), OrbitalAngMom(5), TotalAngMom(1),
              IsospinProj::Neutron(), OccupationNumber::Particle())};

  auto basis = imsrg::SPFullBasis::FromEMax(emax);

  REQUIRE(basis.size() == 30);

  for (const auto& x : sampled_emax2_states) {
    REQUIRE(IsStateInBasis(x, basis));
  }
  for (const auto& x : sampled_emax4_states) {
    REQUIRE(IsStateInBasis(x, basis));
  }

  for (const auto& x : sampled_non_emax4_states) {
    REQUIRE_FALSE(IsStateInBasis(x, basis));
  }
}

TEST_CASE("Test FromEMax factory method (no occs, emax=6).") {
  using imsrg::HOEnergy;

  HOEnergy emax(6);

  auto basis = imsrg::SPFullBasis::FromEMax(emax);

  REQUIRE(basis.size() == 56);
}

TEST_CASE("Test FromEMax factory method (no occs, emax=8).") {
  using imsrg::HOEnergy;

  HOEnergy emax(8);

  auto basis = imsrg::SPFullBasis::FromEMax(emax);

  REQUIRE(basis.size() == 90);
}
