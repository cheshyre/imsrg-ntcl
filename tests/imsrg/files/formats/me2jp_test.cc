// Copyright 2022 Matthias Heinz
#include "imsrg/files/formats/me2jp.h"

#include <string>
#include <type_traits>
#include <utility>

#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/model_space/single_particle/state_string.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

TEST_CASE("Test read-in of Ragnar emax=4 NAT ME2JP Hamiltonian.") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME2JPFile;
  using imsrg::OccupationNumber;
  using imsrg::SPState;
  using imsrg::SPStateString;
  using imsrg::TotalAngMom;

  std::string path_to_file =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me2jp";

  const auto me2jp = ME2JPFile::FromTextFile(path_to_file, HOEnergy(4),
                                             Hermiticity::Hermitian());

  SPState n0s1_2(SPStateString("n0s1/2"), OccupationNumber::Particle());
  SPState p0s1_2(SPStateString("p0s1/2"), OccupationNumber::Particle());
  SPState n0p1_2(SPStateString("n0p1/2"), OccupationNumber::Particle());
  SPState p0p1_2(SPStateString("p0p1/2"), OccupationNumber::Particle());
  SPState n0p3_2(SPStateString("n0p3/2"), OccupationNumber::Particle());
  SPState p0p3_2(SPStateString("p0p3/2"), OccupationNumber::Particle());
  SPState n1s1_2(SPStateString("n1s1/2"), OccupationNumber::Particle());
  SPState p1s1_2(SPStateString("p1s1/2"), OccupationNumber::Particle());
  SPState n1p1_2(SPStateString("n1p1/2"), OccupationNumber::Particle());

  TotalAngMom jj_0(0);
  TotalAngMom jj_2(2);

  SECTION("Allowed by symmetries") {
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0s1_2, n0s1_2, n0s1_2, jj_0) ==
            Approx(-13.187302933647).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0s1_2, n0s1_2, n0s1_2, jj_2) ==
            Approx(0.0).epsilon(1e-5));

    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, n0s1_2, p0s1_2, n0s1_2, jj_0) ==
            Approx(-6.802379901960).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, p0s1_2, p0s1_2, n0s1_2, jj_0) ==
            Approx(-6.802379901960).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, p0s1_2, n0s1_2, p0s1_2, jj_0) ==
            Approx(-6.802379901960).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, n0s1_2, n0s1_2, p0s1_2, jj_0) ==
            Approx(-6.802379901960).epsilon(1e-5));

    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, n0s1_2, p0s1_2, n0s1_2, jj_2) ==
            Approx(-8.418805711231).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, p0s1_2, p0s1_2, n0s1_2, jj_2) ==
            Approx(8.418805711231).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, n0s1_2, n0s1_2, p0s1_2, jj_2) ==
            Approx(8.418805711231).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, p0s1_2, n0s1_2, p0s1_2, jj_2) ==
            Approx(-8.418805711231).epsilon(1e-5));

    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, p0s1_2, p0s1_2, p0s1_2, jj_0) ==
            Approx(-11.354616553188).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, p0s1_2, p0s1_2, p0s1_2, jj_2) ==
            Approx(0.0).epsilon(1e-5));

    REQUIRE(me2jp.Get2BMatrixElement(n0p1_2, n0s1_2, n0p1_2, n0s1_2, jj_0) ==
            Approx(-1.817153409162).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0p1_2, n0p1_2, n0s1_2, jj_0) ==
            Approx(-1.817153409162).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0p1_2, n0s1_2, n0s1_2, n0p1_2, jj_0) ==
            Approx(-1.817153409162).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0p1_2, n0s1_2, n0p1_2, jj_0) ==
            Approx(-1.817153409162).epsilon(1e-5));

    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0p1_2, n0s1_2, n1p1_2, jj_0) ==
            Approx(-0.404961996136).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n1p1_2, n0s1_2, n0p1_2, jj_0) ==
            Approx(-0.404961996136).epsilon(1e-5));
  }

  SECTION("Prohibited by symmetries") {
    REQUIRE(me2jp.Get2BMatrixElement(p0s1_2, n0s1_2, n0s1_2, n0s1_2, jj_0) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, p0s1_2, n0s1_2, n0s1_2, jj_0) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0s1_2, p0s1_2, n0s1_2, jj_0) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me2jp.Get2BMatrixElement(n0s1_2, n0s1_2, n0s1_2, p0s1_2, jj_0) ==
            Approx(0.0).epsilon(1e-5));
  }
}
