// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_111.h"

#include <string>
#include <type_traits>
#include <utility>

#include "imsrg/files/formats/me1j.h"
#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/model_space/single_particle/reference_state.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/one_body/read.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

#include "tests/catch.hpp"

TEST_CASE("Test emax=4 NAT O16 [1, 1] -> 1 commutator (anti-herm, herm).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME1JFile;

  const HOEnergy emax(4);

  const auto ms_1b = imsrg::Scalar1BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  auto h1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::Hermitian());
  auto gen1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::AntiHermitian());

  std::string path_to_h1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me1j";
  std::string path_to_gen1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
      "imaginary-time_Moller_Plesset_gen1.me1j";

  const auto h1_me1j =
      ME1JFile::FromTextFile(path_to_h1_me1j, emax, Hermiticity::Hermitian());
  const auto gen1_me1j = ME1JFile::FromTextFile(path_to_gen1_me1j, emax,
                                                Hermiticity::AntiHermitian());

  imsrg::ReadOperatorFromME1J(h1_me1j, h1);
  imsrg::ReadOperatorFromME1J(gen1_me1j, gen1);

  SECTION("[h1, gen1]") {
    auto expected_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());

    std::string path_to_result_me1j =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm11X_ham1_gen1.me1j";
    const auto result_me1j = ME1JFile::FromTextFile(path_to_result_me1j, emax,
                                                    Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME1J(result_me1j, expected_result);

    imsrg::EvaluateScalar111Commutator(h1, gen1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          REQUIRE(actual_tensor(p, q) == Approx(exp_tensor(p, q)).margin(1e-5));
        }
      }
    }
  }

  SECTION("[gen1, h1]") {
    auto expected_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());

    std::string path_to_result_me1j =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm11X_gen1_ham1.me1j";
    const auto result_me1j = ME1JFile::FromTextFile(path_to_result_me1j, emax,
                                                    Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME1J(result_me1j, expected_result);

    imsrg::EvaluateScalar111Commutator(gen1, h1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          REQUIRE(actual_tensor(p, q) == Approx(exp_tensor(p, q)).margin(1e-5));
        }
      }
    }
  }
}

TEST_CASE("Test emax=6 NAT O16 [1, 1] -> 1 commutator (anti-herm, herm).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME1JFile;

  const HOEnergy emax(6);

  const auto ms_1b = imsrg::Scalar1BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  auto h1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::Hermitian());
  auto gen1 = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
      ms_1b, Hermiticity::AntiHermitian());

  std::string path_to_h1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06.me1j";
  std::string path_to_gen1_me1j =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_06/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
      "imaginary-time_Moller_Plesset_gen1.me1j";

  const auto h1_me1j =
      ME1JFile::FromTextFile(path_to_h1_me1j, emax, Hermiticity::Hermitian());
  const auto gen1_me1j = ME1JFile::FromTextFile(path_to_gen1_me1j, emax,
                                                Hermiticity::AntiHermitian());

  imsrg::ReadOperatorFromME1J(h1_me1j, h1);
  imsrg::ReadOperatorFromME1J(gen1_me1j, gen1);

  SECTION("[h1, gen1]") {
    auto expected_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());

    std::string path_to_result_me1j =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm11X_ham1_gen1.me1j";
    const auto result_me1j = ME1JFile::FromTextFile(path_to_result_me1j, emax,
                                                    Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME1J(result_me1j, expected_result);

    imsrg::EvaluateScalar111Commutator(h1, gen1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          REQUIRE(actual_tensor(p, q) == Approx(exp_tensor(p, q)).margin(1e-5));
        }
      }
    }
  }

  SECTION("[gen1, h1]") {
    auto expected_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar1BOperator::FromScalar1BModelSpace(
        ms_1b, Hermiticity::Hermitian());

    std::string path_to_result_me1j =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_06/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_06_hw_24.00_emax_06_"
        "imaginary-time_Moller_Plesset_comm11X_gen1_ham1.me1j";
    const auto result_me1j = ME1JFile::FromTextFile(path_to_result_me1j, emax,
                                                    Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME1J(result_me1j, expected_result);

    imsrg::EvaluateScalar111Commutator(gen1, h1, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_1b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = expected_result.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = actual_result.GetTensorAtIndex(chan_index);

      const auto dim_p = exp_tensor.dim_size(0);
      const auto dim_q = exp_tensor.dim_size(1);

      for (std::size_t p = 0; p < dim_p; p += 1) {
        for (std::size_t q = 0; q < dim_q; q += 1) {
          REQUIRE(actual_tensor(p, q) == Approx(exp_tensor(p, q)).margin(1e-5));
        }
      }
    }
  }
}
