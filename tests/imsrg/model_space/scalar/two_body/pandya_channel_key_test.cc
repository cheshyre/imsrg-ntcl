// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/scalar/two_body/pandya_channel_key.h"

#include <vector>

#include "imsrg/model_space/scalar/two_body/bare_channel_key.h"
#include "imsrg/model_space/scalar/two_body/channel_key.h"
#include "imsrg/model_space/single_particle/channel_key.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"
#include "tests/helpers/equality.h"

#include "tests/catch.hpp"

TEST_CASE("Test generation of Panyda channels (ps1/2 ps1/2 ps1/2 ps1/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, p_s_1_chankey,
                                     p_s_1_chankey, p_s_1_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (ps1/2 pp1/2 ps1/2 pp1/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey p_p_1_chankey(TotalAngMom(1), Parity::Odd(),
                             IsospinProj::Proton());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, p_p_1_chankey,
                                     p_s_1_chankey, p_p_1_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (ps1/2 pp1/2 pp1/2 ps1/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey p_p_1_chankey(TotalAngMom(1), Parity::Odd(),
                             IsospinProj::Proton());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, p_p_1_chankey,
                                     p_p_1_chankey, p_s_1_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (ps1/2 np1/2 ps1/2 np1/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_1_chankey(TotalAngMom(1), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, n_p_1_chankey,
                                     p_s_1_chankey, n_p_1_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (ps1/2 ps1/2 np1/2 np1/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_1_chankey(TotalAngMom(1), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, p_s_1_chankey,
                                     n_p_1_chankey, n_p_1_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (ps1/2 ps1/2 np3/2 np3/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_s_1_chankey, p_s_1_chankey,
                                     n_p_3_chankey, n_p_3_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (pd3/2 pd3/2 np3/2 np3/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_d_3_chankey(TotalAngMom(3), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_d_3_chankey, p_d_3_chankey,
                                     n_p_3_chankey, n_p_3_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(4)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(6)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (pd5/2 pd5/2 np3/2 np3/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_d_5_chankey(TotalAngMom(5), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_d_5_chankey, p_d_5_chankey,
                                     n_p_3_chankey, n_p_3_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(0)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(2)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(4)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(6)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE("Test generation of Panyda channels (pd5/2 ps1/2 np3/2 np3/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_d_5_chankey(TotalAngMom(5), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey sp_chans = {p_d_5_chankey, p_s_1_chankey,
                                     n_p_3_chankey, n_p_3_chankey};

  const std::vector<Scalar2BPandyaChannelKey> expected = {
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(4)),
      Scalar2BPandyaChannelKey(sp_chans, TotalAngMom(6)),
  };

  const auto actual = imsrg::GeneratePandyaChannels(sp_chans);

  REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
}

TEST_CASE(
    "Test generation of standard channels from Panyda chan (pd5/2 ps1/2 np3/2 "
    "np3/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_d_5_chankey(TotalAngMom(5), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey pandya_sp_chans = {p_d_5_chankey, p_s_1_chankey,
                                            n_p_3_chankey, n_p_3_chankey};

  const std::vector<Scalar2BChannelKey> expected = {
      Scalar2BChannelKey({p_d_5_chankey, n_p_3_chankey},
                         {n_p_3_chankey, p_s_1_chankey}, TotalAngMom(2)),
      Scalar2BChannelKey({p_d_5_chankey, n_p_3_chankey},
                         {n_p_3_chankey, p_s_1_chankey}, TotalAngMom(4)),
  };

  SECTION("jj_2b = 4") {
    TotalAngMom jj_2b(4);
    Scalar2BPandyaChannelKey pandya_chan(pandya_sp_chans, jj_2b);
    const auto actual = pandya_chan.StandardChannels();

    REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
  }

  SECTION("jj_2b = 6") {
    TotalAngMom jj_2b(6);
    Scalar2BPandyaChannelKey pandya_chan(pandya_sp_chans, jj_2b);
    const auto actual = pandya_chan.StandardChannels();

    REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
  }
}

TEST_CASE(
    "Test generation of standard channels from Panyda chan (pd5/2 ps1/2 np3/2 "
    "nf5/2).") {
  using imsrg::IsospinProj;
  using imsrg::Parity;
  using imsrg::Scalar2BBareChannelKey;
  using imsrg::Scalar2BChannelKey;
  using imsrg::Scalar2BPandyaChannelKey;
  using imsrg::SPChannelKey;
  using imsrg::TotalAngMom;

  SPChannelKey p_d_5_chankey(TotalAngMom(5), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey p_s_1_chankey(TotalAngMom(1), Parity::Even(),
                             IsospinProj::Proton());
  SPChannelKey n_p_3_chankey(TotalAngMom(3), Parity::Odd(),
                             IsospinProj::Neutron());
  SPChannelKey n_f_5_chankey(TotalAngMom(5), Parity::Odd(),
                             IsospinProj::Neutron());
  Scalar2BBareChannelKey pandya_sp_chans = {p_d_5_chankey, p_s_1_chankey,
                                            n_p_3_chankey, n_f_5_chankey};

  const std::vector<Scalar2BChannelKey> expected = {
      Scalar2BChannelKey({p_d_5_chankey, n_f_5_chankey},
                         {n_p_3_chankey, p_s_1_chankey}, TotalAngMom(2)),
      Scalar2BChannelKey({p_d_5_chankey, n_f_5_chankey},
                         {n_p_3_chankey, p_s_1_chankey}, TotalAngMom(4)),
  };

  SECTION("jj_2b = 4") {
    TotalAngMom jj_2b(4);
    Scalar2BPandyaChannelKey pandya_chan(pandya_sp_chans, jj_2b);
    const auto actual = pandya_chan.StandardChannels();

    REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
  }

  SECTION("jj_2b = 6") {
    TotalAngMom jj_2b(6);
    Scalar2BPandyaChannelKey pandya_chan(pandya_sp_chans, jj_2b);
    const auto actual = pandya_chan.StandardChannels();

    REQUIRE(imsrg::test::AreVectorsEqual(expected, actual));
  }
}
