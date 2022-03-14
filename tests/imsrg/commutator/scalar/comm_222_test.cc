// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_222.h"

#include <string>
#include <type_traits>
#include <utility>

#include "imsrg/files/formats/me2jp.h"
#include "imsrg/model_space/scalar/two_body/model_space.h"
#include "imsrg/model_space/single_particle/full_basis.h"
#include "imsrg/model_space/single_particle/model_space.h"
#include "imsrg/model_space/single_particle/reference_state.h"
#include "imsrg/operator/scalar/two_body/operator.h"
#include "imsrg/operator/scalar/two_body/read.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

#include "tests/catch.hpp"

TEST_CASE("Test emax=4 NAT O16 [2, 2] -> 2 commutator (anti-herm, herm).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME2JPFile;

  const HOEnergy emax(4);

  const auto ms_2b = imsrg::Scalar2BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  auto h2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::Hermitian());
  auto gen2 = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
      ms_2b, Hermiticity::AntiHermitian());

  std::string path_to_h2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04.me2jp";
  std::string path_to_gen2_me2jp =
      "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
      "calc_emax_04/"
      "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
      "imaginary-time_Moller_Plesset_gen2.me2jp";

  const auto h2_me2jp =
      ME2JPFile::FromTextFile(path_to_h2_me2jp, emax, Hermiticity::Hermitian());
  const auto gen2_me2jp = ME2JPFile::FromTextFile(path_to_gen2_me2jp, emax,
                                                  Hermiticity::AntiHermitian());

  imsrg::ReadOperatorFromME2JP(h2_me2jp, h2);
  imsrg::ReadOperatorFromME2JP(gen2_me2jp, gen2);

  SECTION("[gen2, h2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm22X_gen2_ham2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar222Commutator(gen2, h2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_2b->NumberOfChannels();
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

  SECTION("[h2, gen2]") {
    auto expected_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());
    auto actual_result = imsrg::Scalar2BOperator::FromScalar2BModelSpace(
        ms_2b, Hermiticity::Hermitian());

    std::string path_to_result_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_comm22X_ham2_gen2.me2jp";
    const auto result_me2jp = ME2JPFile::FromTextFile(
        path_to_result_me2jp, emax, Hermiticity::Hermitian());

    imsrg::ReadOperatorFromME2JP(result_me2jp, expected_result);

    imsrg::EvaluateScalar222Commutator(h2, gen2, actual_result);

    for (std::size_t chan_index = 0; chan_index < ms_2b->NumberOfChannels();
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
