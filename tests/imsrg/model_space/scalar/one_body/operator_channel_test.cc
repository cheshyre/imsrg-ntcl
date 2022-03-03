// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/one_body/operator_channel.h"

#include <type_traits>
#include <utility>

#include "absl/hash/hash_testing.h"

#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

#include "tests/catch.hpp"

TEST_CASE("Test proper abseil hash.") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar1BOpChannel;
  using imsrg::TotalAngMom;
  REQUIRE(absl::VerifyTypeImplementsAbslHashCorrectly(
      {Scalar1BOpChannel(TotalAngMom(1), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(3), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(5), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(7), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(9), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(11), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(13), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(15), Parity::Even(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(1), Parity::Even(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(3), Parity::Even(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(5), Parity::Even(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(7), Parity::Even(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(9), Parity::Even(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(11), Parity::Even(),
                         IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(13), Parity::Even(),
                         IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(15), Parity::Even(),
                         IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(1), Parity::Odd(), IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(3), Parity::Odd(), IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(5), Parity::Odd(), IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(7), Parity::Odd(), IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(9), Parity::Odd(), IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(11), Parity::Odd(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(13), Parity::Odd(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(15), Parity::Odd(),
                         IsospinProj::Neutron()),
       Scalar1BOpChannel(TotalAngMom(1), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(3), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(5), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(7), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(9), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(11), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(13), Parity::Odd(), IsospinProj::Proton()),
       Scalar1BOpChannel(TotalAngMom(15), Parity::Odd(),
                         IsospinProj::Proton())}));
}
