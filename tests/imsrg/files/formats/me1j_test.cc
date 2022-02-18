// Copyright 2022 Matthias Heinz
#include "imsrg/files/formats/me1j.h"

#include <string>
#include <type_traits>
#include <utility>

#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/model_space/single_particle/state_string.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

#include "tests/catch.hpp"

TEST_CASE("Test read-in of Ragnar emax=4 NAT ME1J Hamiltonian.") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME1JFile;
  using imsrg::OccupationNumber;
  using imsrg::SPState;
  using imsrg::SPStateString;

  std::string path_to_file =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me1j";

  const auto me1j = ME1JFile::FromTextFile(path_to_file, HOEnergy(4),
                                           Hermiticity::Hermitian());

  REQUIRE(me1j.Get0BPart() == Approx(-11.2193398436).epsilon(1e-5));

  SPState n0s1_2(SPStateString("n0s1/2"), OccupationNumber::Particle());
  SPState p0s1_2(SPStateString("p0s1/2"), OccupationNumber::Particle());
  SPState n0p1_2(SPStateString("n0p1/2"), OccupationNumber::Particle());
  SPState p0p1_2(SPStateString("p0p1/2"), OccupationNumber::Particle());
  SPState n0p3_2(SPStateString("n0p3/2"), OccupationNumber::Particle());
  SPState p0p3_2(SPStateString("p0p3/2"), OccupationNumber::Particle());
  SPState n1s1_2(SPStateString("n1s1/2"), OccupationNumber::Particle());
  SPState p1s1_2(SPStateString("p1s1/2"), OccupationNumber::Particle());

  SECTION("Allowed by symmetries") {
    REQUIRE(me1j.Get1BMatrixElement(n0s1_2, n0s1_2) ==
            Approx(-42.596206348055).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0s1_2, p0s1_2) ==
            Approx(-38.422543350179).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n0p1_2, n0p1_2) ==
            Approx(-11.208007715079).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0p1_2, p0p1_2) ==
            Approx(-7.268378287724).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n0p3_2, n0p3_2) ==
            Approx(-18.694839908723).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0p3_2, p0p3_2) ==
            Approx(-14.677726887030).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n1s1_2, n1s1_2) ==
            Approx(15.265075691710).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n1s1_2, n0s1_2) ==
            Approx(-0.325566592806).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n0s1_2, n1s1_2) ==
            Approx(-0.325566592806).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p1s1_2, p1s1_2) ==
            Approx(19.306670490911).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p1s1_2, p0s1_2) ==
            Approx(-0.234885691021).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0s1_2, p1s1_2) ==
            Approx(-0.234885691021).epsilon(1e-5));
  }

  SECTION("Prohibited by symmetries") {
    REQUIRE(me1j.Get1BMatrixElement(n0s1_2, p0s1_2) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0s1_2, n0s1_2) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n0s1_2, n0p1_2) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0s1_2, p0p1_2) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(n0s1_2, n0p1_2) ==
            Approx(0.0).epsilon(1e-5));
    REQUIRE(me1j.Get1BMatrixElement(p0s1_2, p0p1_2) ==
            Approx(0.0).epsilon(1e-5));
  }
}
