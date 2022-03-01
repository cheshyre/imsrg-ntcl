// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_122.h"

#include <string>
#include <type_traits>
#include <utility>

#include "imsrg/files/formats/me1j.h"
#include "imsrg/files/formats/me2jp.h"
#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/model_space/scalar/two_body/model_space.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/model_space/single_particle/reference_state.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/one_body/read.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/operator/scalar/two_body/read.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

#include "tests/catch.hpp"

TEST_CASE("Test emax=4 NAT O16 [1, 2] -> 2 commutator (anti-herm, herm).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME1JFile;
  using imsrg::ME2JPFile;

  const HOEnergy emax(4);

  const auto ms_1b = imsrg::Scalar1BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  const auto ms_2b = imsrg::Scalar2BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  auto h1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::Hermitian());
  auto gen1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::AntiHermitian());

  auto h2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::Hermitian());
  auto gen2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::AntiHermitian());

  std::string path_to_h1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me1j";
  std::string path_to_gen1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
      "imaginary-time_Moller_Plesset_gen1.me1j";
  std::string path_to_h2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me2jp";
  std::string path_to_gen2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
      "imaginary-time_Moller_Plesset_gen2.me2jp";

  const auto h1_me1j =
      ME1JFile::FromTextFile(path_to_h1_me1j, emax, Hermiticity::Hermitian());
  const auto gen1_me1j = ME1JFile::FromTextFile(path_to_gen1_me1j, emax,
                                                Hermiticity::AntiHermitian());

  const auto h2_me2jp =
      ME2JPFile::FromTextFile(path_to_h2_me2jp, emax, Hermiticity::Hermitian());
  const auto gen2_me2jp = ME2JPFile::FromTextFile(path_to_gen2_me2jp, emax,
                                                  Hermiticity::AntiHermitian());

  imsrg::ReadOperatorFromME1J(h1_me1j, h1);
  imsrg::ReadOperatorFromME1J(gen1_me1j, gen1);
  imsrg::ReadOperatorFromME2JP(h2_me2jp, h2);
  imsrg::ReadOperatorFromME2JP(gen2_me2jp, gen2);

  SECTION("[gen1, h2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm12X_gen1_ham2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar122Commutator(gen1, h2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[h1, gen2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm12X_ham1_gen2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar122Commutator(h1, gen2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[gen2, h1]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm21X_gen2_ham1.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar212Commutator(gen2, h1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[h2, gen1]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm21X_ham2_gen1.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar212Commutator(h2, gen1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("Test emax=6 NAT O16 [1, 2] -> 2 commutator (anti-herm, herm).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME1JFile;
  using imsrg::ME2JPFile;

  const HOEnergy emax(6);

  const auto ms_1b = imsrg::Scalar1BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  const auto ms_2b = imsrg::Scalar2BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  auto h1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::Hermitian());
  auto gen1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::AntiHermitian());

  auto h2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::Hermitian());
  auto gen2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::AntiHermitian());

  std::string path_to_h1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06.me1j";
  std::string path_to_gen1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
      "imaginary-time_Moller_Plesset_gen1.me1j";
  std::string path_to_h2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06.me2jp";
  std::string path_to_gen2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
      "imaginary-time_Moller_Plesset_gen2.me2jp";

  const auto h1_me1j =
      ME1JFile::FromTextFile(path_to_h1_me1j, emax, Hermiticity::Hermitian());
  const auto gen1_me1j = ME1JFile::FromTextFile(path_to_gen1_me1j, emax,
                                                Hermiticity::AntiHermitian());

  const auto h2_me2jp =
      ME2JPFile::FromTextFile(path_to_h2_me2jp, emax, Hermiticity::Hermitian());
  const auto gen2_me2jp = ME2JPFile::FromTextFile(path_to_gen2_me2jp, emax,
                                                  Hermiticity::AntiHermitian());

  imsrg::ReadOperatorFromME1J(h1_me1j, h1);
  imsrg::ReadOperatorFromME1J(gen1_me1j, gen1);
  imsrg::ReadOperatorFromME2JP(h2_me2jp, h2);
  imsrg::ReadOperatorFromME2JP(gen2_me2jp, gen2);

  SECTION("[gen1, h2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm12X_gen1_ham2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar122Commutator(gen1, h2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[h1, gen2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm12X_ham1_gen2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar122Commutator(h1, gen2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[gen2, h1]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm21X_gen2_ham1.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar212Commutator(gen2, h1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }

  SECTION("[h2, gen1]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm21X_ham2_gen1.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar212Commutator(h2, gen1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);
      const auto dim_r = exp_tensor.dim_size(2);
      const auto dim_s = exp_tensor.dim_size(3);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          for (std::size_t r = 0; r < dim_r; r += 1) {
            for (std::size_t s = 0; s < dim_s; s += 1) {
              REQUIRE(actual_tensor(p, q, r, s) ==
                      Approx(exp_tensor(p, q, r, s)).margin(1e-5));
            }
          }
        }
      }
    }
  }
}
