// Copyright 2022 Matthias Heinz
#include "imsrg/files/formats/me1j.h"

#include <fstream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include "imsrg/assert.h"
#include "imsrg/error.h"
#include "imsrg/files/formats/helpers/mexj.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

namespace imsrg {

namespace detail {
static std::size_t GetME1JSize(imsrg::HOEnergy emax);
static absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t>
MakeME1JIndexLookup(imsrg::HOEnergy emax);
template <typename S>
static std::tuple<double, std::vector<double>> ReadFile(S&& stream,
                                                        HOEnergy emax);
template <typename S>
static imsrg::ValidationResult ValidateFile(S&& stream, HOEnergy emax);
static imsrg::ValidationResult ValidateHeader(std::string_view header);
}  // namespace detail

ME1JFile ME1JFile::FromTextFile(std::string path_to_file, HOEnergy emax,
                                Hermiticity herm) {
  std::ifstream file(path_to_file);
  imsrg::CheckForError(
      !file.is_open(),
      fmt::format("Failed to open ME1J text file at {}", path_to_file));
  auto [me_0b, mes] = imsrg::detail::ReadFile(std::move(file), emax);
  return ME1JFile(me_0b, herm, std::move(mes),
                  imsrg::detail::MakeME1JIndexLookup(emax));
}

// ME1JFile ME1JFile::FromGZippedFile(std::string path_to_file, HOEnergy emax,
//                                    Hermiticity herm) {
//   (void)path_to_file;
//   (void)emax;
//   imsrg::Error("ME1J::FromGZippedFile not implemented.");
// }

// ME1JFile ME1JFile::FromBinary(std::string path_to_file, HOEnergy emax,
//                               Hermiticity herm) {
//   (void)path_to_file;
//   (void)emax;
//   imsrg::Error("ME1J::FromBinary not implemented.");
//   // This implementation will need to different from those above.
// }

ME1JFile::ME1JFile(
    double me_0b, Hermiticity herm, std::vector<double>&& mes,
    absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t>&& me_lookup)
    : me_0b_(me_0b),
      herm_(herm),
      mes_(std::move(mes)),
      me_lookup_(std::move(me_lookup)) {}

double ME1JFile::Get1BMatrixElement(const SPState& p, const SPState& q) const {
  using imsrg::mexj::NLJJT;
  using imsrg::mexj::NLJJTIndex2;
  using std::swap;

  NLJJT nljjt_p(p);
  NLJJT nljjt_q(q);

  int factor = 1;
  if (nljjt_q.Index() > nljjt_p.Index()) {
    factor *= herm_.Factor();
    swap(nljjt_p, nljjt_q);
  }

  NLJJTIndex2 lookup_key(nljjt_p.Index(), nljjt_q.Index());

  const auto search = me_lookup_.find(lookup_key);
  if (search == me_lookup_.end()) {
    return 0.0;
  }
  return factor * mes_[search->second];
}

namespace detail {

template <typename S>
std::tuple<double, std::vector<double>> ReadFile(S&& stream, HOEnergy emax) {
  // Process header
  std::string header;
  std::getline(stream, header);
  {
    const auto [valid_header, msg] = ValidateHeader(header);
    imsrg::CheckForError(!valid_header, msg);
  }

  // Get 0B part
  double me_0b;
  stream >> me_0b;

  // Read 1B MEs
  const auto size = GetME1JSize(emax);
  std::vector<double> mes(size, 0.0);
  for (std::size_t i = 0; i < size; i += 1) {
    stream >> mes[i];
  }

  return {me_0b, mes};
}

template <typename S>
imsrg::ValidationResult ValidateFile(S&& stream, HOEnergy emax) {
  // Process header
  std::string header;
  std::getline(stream, header);
  const auto valid_header = ValidateHeader(header);
  if (!valid_header.valid) {
    return valid_header;
  }

  // Get 0B part
  double me_0b;
  stream >> me_0b;
  if (!stream) {
    return {false, "Reached end of ME1J file before zero-body part was read."};
  }

  double me_1b;
  const auto size = GetME1JSize(emax);
  for (std::size_t i = 0; i < size; i += 1) {
    stream >> me_1b;
    if (!stream) {
      return {false,
              fmt::format(
                  "Reached end of ME1J file before one-body matrix element {} "
                  "was read.",
                  i)};
    }
  }

  // Will not check for file too long.
  // This makes it possible to read from larger emax file.

  return {true};
}

// Formula comes from storing lower triangle including diagonal.
// The NLJJT basis size is always even by virtue of having
// exactly the same proton *and* neutron orbitals.
std::size_t GetME1JSize(imsrg::HOEnergy emax) {
  const auto basis = imsrg::mexj::GetNLJJTs(emax);
  const auto size = basis.size();
  Expects(size % 2 == 0);
  return size * size / 2 - size / 2 + size;
}

absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t> MakeME1JIndexLookup(
    imsrg::HOEnergy emax) {
  using imsrg::mexj::NLJJTIndex2;
  const auto basis = imsrg::mexj::GetNLJJTs(emax);
  absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t> me_lookup;
  me_lookup.reserve(GetME1JSize(emax));

  std::size_t current_index = 0;
  for (const auto& p : basis) {
    for (const auto& q : basis) {
      if (q.Index() <= p.Index()) {
        me_lookup[NLJJTIndex2(p.Index(), q.Index())] = current_index;
        current_index += 1;
      }
    }
  }
  return me_lookup;
}

imsrg::ValidationResult ValidateHeader(std::string_view header) {
  if (header.find("me1j") == std::string::npos) {
    // me1j substring was not found, so header is invalid
    return {false, fmt::format("Header \"{}\" is invalid for ME1J.", header)};
  }
  return {true};
}

}  // namespace detail
}  // namespace imsrg
