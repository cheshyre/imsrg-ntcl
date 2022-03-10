// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/two_body/operator.h"

#include "imsrg/files/formats/me2jp.h"
#include "imsrg/model_space/scalar/two_body/pandya_channel_key.h"
#include "imsrg/operator/scalar/two_body/read.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

#include "tests/catch.hpp"

TEST_CASE("Test double Panyda is identity (emax=4).") {
  using imsrg::Hermiticity;
  using imsrg::HOEnergy;
  using imsrg::ME2JPFile;

  const HOEnergy emax(4);

  const auto ms_2b = imsrg::Scalar2BModelSpace::FromSPModelSpace(
      imsrg::SPModelSpace::FromFullBasis(
          imsrg::SPFullBasis::FromEMaxAndReferenceState(
              emax, imsrg::ReferenceState::O16())));

  SECTION("with 2B Hamiltonian.") {
    const auto herm = Hermiticity::Hermitian();
    auto op = imsrg::Scalar2BOperator::FromScalar2BModelSpace(ms_2b, herm);
    auto op_out = imsrg::Scalar2BOperator::FromScalar2BModelSpace(ms_2b, herm);

    std::string path_to_op_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04."
        "me2jp";

    const auto op_me2jp = ME2JPFile::FromTextFile(path_to_op_me2jp, emax, herm);
    imsrg::ReadOperatorFromME2JP(op_me2jp, op);

    for (const auto sp_chans : ms_2b->BareChannels()) {
      const auto pandya_chans = imsrg::GeneratePandyaChannels(
          imsrg::BareChannelKeyPandyaSwap(sp_chans));
      for (const auto pandya_chan : pandya_chans) {
        const auto panyda_tensor =
            op.GeneratePandyaTensorInPandyaChannel(pandya_chan);
        op_out.AddPandyaTensor(pandya_chan, panyda_tensor);
      }
    }

    for (std::size_t chan_index = 0; chan_index < ms_2b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = op.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = op_out.GetTensorAtIndex(chan_index);

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

  SECTION("with 2B generator.") {
    const auto herm = Hermiticity::AntiHermitian();
    auto op = imsrg::Scalar2BOperator::FromScalar2BModelSpace(ms_2b, herm);
    auto op_out = imsrg::Scalar2BOperator::FromScalar2BModelSpace(ms_2b, herm);

    std::string path_to_op_me2jp =
        "tests/data/from_ragnar/NN-only/O16/EMN500_N3LO/NAT/hw_24.00/"
        "calc_emax_04/"
        "HNO_O16_NN-only_EMN500_N3LO_NAT_mf_calc_emax_04_hw_24.00_emax_04_"
        "imaginary-time_Moller_Plesset_gen2.me2jp";

    const auto op_me2jp = ME2JPFile::FromTextFile(path_to_op_me2jp, emax, herm);
    imsrg::ReadOperatorFromME2JP(op_me2jp, op);

    for (const auto sp_chans : ms_2b->BareChannels()) {
      const auto pandya_chans = imsrg::GeneratePandyaChannels(
          imsrg::BareChannelKeyPandyaSwap(sp_chans));
      for (const auto pandya_chan : pandya_chans) {
        const auto panyda_tensor =
            op.GeneratePandyaTensorInPandyaChannel(pandya_chan);
        op_out.AddPandyaTensor(pandya_chan, panyda_tensor);
      }
    }

    for (std::size_t chan_index = 0; chan_index < ms_2b->NumberOfChannels();
         chan_index += 1) {
      const auto& exp_tensor = op.GetTensorAtIndex(chan_index);
      const auto& actual_tensor = op_out.GetTensorAtIndex(chan_index);

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
