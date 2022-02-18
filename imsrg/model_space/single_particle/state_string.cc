// Copyright 2022 Matthias Heinz
#include "imsrg/model_space/single_particle/state_string.h"

#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "fmt/core.h"

#include "imsrg/assert.h"
#include "imsrg/error.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {
imsrg::RadialExcitationNumber ParseRadialNFromString(std::string_view str);
imsrg::OrbitalAngMom ParseLFromString(std::string_view str);
imsrg::TotalAngMom ParseJJFromString(std::string_view str);
imsrg::IsospinProj ParseM_TTFromString(std::string_view str);
}  // namespace detail

std::string SPStateString::BasicString(RadialExcitationNumber n,
                                       OrbitalAngMom l, TotalAngMom jj,
                                       IsospinProj m_tt) {
  Expects((m_tt == IsospinProj::Proton()) || (m_tt == IsospinProj::Neutron()));
  const auto ls = SPStateString::OrbitalAngMomLookup();
  if (m_tt == IsospinProj::Proton()) {
    return fmt::format("p{}{}{}/2", n.AsInt(), ls[l.AsInt()], jj.AsInt());
  }
  return fmt::format("n{}{}{}/2", n.AsInt(), ls[l.AsInt()], jj.AsInt());
}

SPStateString::SPStateString(RadialExcitationNumber n, OrbitalAngMom l,
                             TotalAngMom jj, IsospinProj m_tt)
    : str_(SPStateString::BasicString(n, l, jj, m_tt)),
      n_(n),
      l_(l),
      jj_(jj),
      m_tt_(m_tt) {}

SPStateString::SPStateString(std::string_view state_string)
    : str_(state_string),
      n_(imsrg::detail::ParseRadialNFromString(str_)),
      l_(imsrg::detail::ParseLFromString(str_)),
      jj_(imsrg::detail::ParseJJFromString(str_)),
      m_tt_(imsrg::detail::ParseM_TTFromString(str_)) {}

std::vector<std::string> SPStateString::OrbitalAngMomLookup() {
  return {"s", "p", "d", "f", "g", "h", "i", "j", "k"};
}

std::vector<std::string> SPStateString::CanonicallyOrderedOrbitals() {
  return {"0s1/2",
          // Full shell closure
          "0p3/2", "0p1/2",
          // Full shell closure
          "0d5/2", "1s1/2", "0d3/2",
          // Full shell closure
          "0f7/2",
          // "Full" shell closure
          "1p3/2", "0f5/2", "1p1/2", "0g9/2",
          // "Full" shell closure
          "1d5/2", "0g7/2", "2s1/2", "1d3/2"};
}
std::vector<std::string> SPStateString::CanonicallyOrderedProtonOrbitals() {
  const auto orbitals_no_m_tt = SPStateString::CanonicallyOrderedOrbitals();
  std::vector<std::string> orbitals;
  orbitals.reserve(orbitals_no_m_tt.size());
  for (const auto& orb : orbitals_no_m_tt) {
    orbitals.push_back("p" + orb);
  }
  return orbitals;
}
std::vector<std::string> SPStateString::CanonicallyOrderedNeutronOrbitals() {
  const auto orbitals_no_m_tt = SPStateString::CanonicallyOrderedOrbitals();
  std::vector<std::string> orbitals;
  orbitals.reserve(orbitals_no_m_tt.size());
  for (const auto& orb : orbitals_no_m_tt) {
    orbitals.push_back("n" + orb);
  }
  return orbitals;
}
std::vector<SPStateString> SPStateString::GetProtonOrbitalsUpToMax(
    const SPStateString& max_state) {
  Expects(max_state.M_TT() == IsospinProj::Proton());
  const auto proton_strings = SPStateString::CanonicallyOrderedProtonOrbitals();
  std::vector<SPStateString> orbs;

  for (const auto& p_str : proton_strings) {
    orbs.push_back(SPStateString(p_str));
    if (orbs.back() == max_state) {
      return orbs;
    }
  }

  imsrg::Error(
      fmt::format("State {} was not found in the available proton orbitals.",
                  max_state.String()));
  // Unreachable
  return orbs;
}
std::vector<SPStateString> SPStateString::GetNeutronOrbitalsUpToMax(
    const SPStateString& max_state) {
  Expects(max_state.M_TT() == IsospinProj::Neutron());
  const auto neutron_strings =
      SPStateString::CanonicallyOrderedNeutronOrbitals();
  std::vector<SPStateString> orbs;

  for (const auto& n_str : neutron_strings) {
    orbs.push_back(SPStateString(n_str));
    if (orbs.back() == max_state) {
      return orbs;
    }
  }

  imsrg::Error(
      fmt::format("State {} was not found in the available neutron orbitals.",
                  max_state.String()));
  // Unreachable
  return orbs;
}

bool operator==(const SPStateString& a, const SPStateString& b) {
  return (a.String() == b.String()) && (a.RadialN() == b.RadialN()) &&
         (a.L() == b.L()) && (a.JJ() == b.JJ()) && (a.M_TT() == b.M_TT());
}

namespace detail {
imsrg::RadialExcitationNumber ParseRadialNFromString(std::string_view str) {
  std::string n_str(str.substr(1, 1));
  try {
    int n_i = std::stoi(n_str);
    return imsrg::RadialExcitationNumber(n_i);
  } catch (const std::invalid_argument& e) {
    imsrg::Error(fmt::format(
        "Could not parse valid RadialN from orbital string {}, found {}", str,
        n_str));
    // Unreachable
    return imsrg::RadialExcitationNumber(0);
  }
}
imsrg::OrbitalAngMom ParseLFromString(std::string_view str) {
  const auto ls = SPStateString::OrbitalAngMomLookup();
  int ls_size = ls.size();
  std::string l_str(str.substr(2, 1));
  for (int l = 0; l < ls_size; l += 1) {
    if (ls[l] == l_str) {
      return imsrg::OrbitalAngMom(l);
    }
  }
  imsrg::Error(fmt::format(
      "Could not parse valid L from orbital string {}, found {}", str, l_str));
  // Unreachable
  return imsrg::OrbitalAngMom(0);
}
imsrg::TotalAngMom ParseJJFromString(std::string_view str) {
  std::string jj_str(str.substr(3, str.size() - 3));
  std::string jj_str_red(jj_str.substr(0, jj_str.size() - 2));
  try {
    int jj_i = std::stoi(jj_str_red);
    return imsrg::TotalAngMom(jj_i);
  } catch (const std::invalid_argument& e) {
    imsrg::Error(
        fmt::format("Could not parse valid JJ from orbital string {}, found {} "
                    "with jj = {}",
                    str, jj_str, jj_str_red));
    // Unreachable
    return imsrg::TotalAngMom(0);
  }
}
imsrg::IsospinProj ParseM_TTFromString(std::string_view str) {
  std::string m_tt_str(str.substr(0, 1));
  if (m_tt_str == "p") {
    return imsrg::IsospinProj::Proton();
  } else if (m_tt_str == "n") {
    return imsrg::IsospinProj::Neutron();
  }
  imsrg::Error(
      fmt::format("Could not parse valid M_TT from orbital string {}, found {}",
                  str, m_tt_str));
  // Unreachable
  return imsrg::IsospinProj(0);
}
}  // namespace detail

}  // namespace imsrg
