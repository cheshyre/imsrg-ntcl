// Copyright 2022 Matthias Heinz
#include "imsrg/files/formats/me2jp.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/error.h"
#include "imsrg/files/formats/helpers/mexj.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"
#include "imsrg/quantum_numbers/coupling/phases.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace detail {

static std::size_t GetME2JPSize(imsrg::HOEnergy emax);

static std::size_t GetME2JPSize_NoJJ(imsrg::HOEnergy emax);

static absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t>
MakeME2JPIndexLookup(imsrg::HOEnergy emax);

template <typename S>
static std::vector<double> ReadFile(S&& stream, HOEnergy emax);

template <typename S>
static imsrg::ValidationResult ValidateFile(S&& stream, HOEnergy emax);

static imsrg::ValidationResult ValidateHeader(std::string_view header);

}  // namespace detail

ME2JPFile ME2JPFile::FromTextFile(std::string path_to_file, HOEnergy emax,
                                  Hermiticity herm) {
  std::ifstream file(path_to_file);
  imsrg::CheckForError(
      !file.is_open(),
      fmt::format("Failed to open ME2JP text file at {}", path_to_file));
  auto mes = imsrg::detail::ReadFile(std::move(file), emax);
  return ME2JPFile(herm, std::move(mes),
                   imsrg::detail::MakeME2JPIndexLookup(emax));
}
// ME2JPFile  ME2JPFile::FromGZippedFile(std::string path_to_file, HOEnergy
// emax,
//                                  Hermiticity herm) = delete;
// ME2JPFile  ME2JPFile::FromBinary(std::string path_to_file, HOEnergy emax,
//                             Hermiticity herm) = delete;

double ME2JPFile::Get2BMatrixElement(const SPState& p, const SPState& q,
                                     const SPState& r, const SPState& s,
                                     TotalAngMom jj_2b) const {
  using imsrg::mexj::NLJJT;
  using imsrg::mexj::NLJJTIndex4;
  using std::swap;

  NLJJT nljjt_p(p);
  NLJJT nljjt_q(q);
  NLJJT nljjt_r(r);
  NLJJT nljjt_s(s);

  int factor = 1;
  if (nljjt_q.Index() > nljjt_p.Index()) {
    factor *= (imsrg::JJPhase::MinusOne() * nljjt_p.JJ().Phase() *
               nljjt_q.JJ().Phase() * jj_2b.Phase(-1))
                  .AsInt();
    swap(nljjt_p, nljjt_q);
  }
  if (nljjt_s.Index() > nljjt_r.Index()) {
    factor *= (imsrg::JJPhase::MinusOne() * nljjt_r.JJ().Phase() *
               nljjt_s.JJ().Phase() * jj_2b.Phase(-1))
                  .AsInt();
    swap(nljjt_r, nljjt_s);
  }
  if ((nljjt_r.Index() > nljjt_p.Index()) ||
      ((nljjt_r.Index() == nljjt_p.Index()) &&
       (nljjt_s.Index() > nljjt_q.Index()))) {
    factor *= herm_.Factor();
    swap(nljjt_r, nljjt_p);
    swap(nljjt_s, nljjt_q);
  }

  NLJJTIndex4 lookup_key(nljjt_p.Index(), nljjt_q.Index(), nljjt_r.Index(),
                         nljjt_s.Index());

  const auto search = me_lookup_.find(lookup_key);
  if (search == me_lookup_.end()) {
    return 0.0;
  }

  const std::size_t base_index = search->second;

  // Handle JJ coupling
  const auto jj_min = std::max(
      imsrg::CouplingMinimum<imsrg::TotalAngMom>(nljjt_p.JJ(), nljjt_q.JJ()),
      imsrg::CouplingMinimum<imsrg::TotalAngMom>(nljjt_r.JJ(), nljjt_s.JJ()));
  const auto jj_max = std::max(
      imsrg::CouplingMaximum<imsrg::TotalAngMom>(nljjt_p.JJ(), nljjt_q.JJ()),
      imsrg::CouplingMaximum<imsrg::TotalAngMom>(nljjt_r.JJ(), nljjt_s.JJ()));

  if ((jj_2b < jj_min) || (jj_2b > jj_max)) {
    return 0.0;
  }

  const std::size_t jj_offset = (jj_2b.AsInt() - jj_min.AsInt()) / 2;

  return factor * mes_[base_index + jj_offset];
}

ME2JPFile::ME2JPFile(
    Hermiticity herm, std::vector<double>&& mes,
    absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t>&& me_lookup)
    : herm_(herm), mes_(std::move(mes)), me_lookup_(std::move(me_lookup)) {}

namespace detail {

std::size_t GetME2JPSize(imsrg::HOEnergy emax) {
  const auto basis = imsrg::mexj::GetNLJJTs(emax);

  std::size_t counter = 0;

  for (const auto& nljjt_p : basis) {
    for (const auto& nljjt_q : basis) {
      // q <= p
      if (nljjt_q.Index() > nljjt_p.Index()) {
        continue;
      }
      for (const auto& nljjt_r : basis) {
        // r, s <= p, q (part 1)
        if (nljjt_r.Index() > nljjt_p.Index()) {
          continue;
        }
        for (const auto& nljjt_s : basis) {
          // s <= r
          if (nljjt_s.Index() > nljjt_r.Index()) {
            continue;
          }
          // r, s <= p, q (part 2)
          if ((nljjt_r.Index() == nljjt_p.Index()) &&
              (nljjt_s.Index() > nljjt_q.Index())) {
            continue;
          }
          // parity
          if (nljjt_p.P() + nljjt_q.P() != nljjt_r.P() + nljjt_s.P()) {
            continue;
          }
          // isospin
          if (nljjt_p.M_TT() + nljjt_q.M_TT() !=
              nljjt_r.M_TT() + nljjt_s.M_TT()) {
            continue;
          }
          const auto jj_pq_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_pq_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_rs_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_rs_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_2_min = std::max(jj_pq_min, jj_rs_min);
          const auto jj_2_max = std::min(jj_pq_max, jj_rs_max);

          const auto range_size =
              imsrg::CouplingRangeFromMinAndMax<imsrg::TotalAngMom>(jj_2_min,
                                                                    jj_2_max)
                  .size();

          counter += range_size;
        }
      }
    }
  }

  return counter;
}

std::size_t GetME2JPSize_NoJJ(imsrg::HOEnergy emax) {
  const auto basis = imsrg::mexj::GetNLJJTs(emax);

  std::size_t counter = 0;

  for (const auto& nljjt_p : basis) {
    for (const auto& nljjt_q : basis) {
      // q <= p
      if (nljjt_q.Index() > nljjt_p.Index()) {
        continue;
      }
      for (const auto& nljjt_r : basis) {
        // r, s <= p, q (part 1)
        if (nljjt_r.Index() > nljjt_p.Index()) {
          continue;
        }
        for (const auto& nljjt_s : basis) {
          // s <= r
          if (nljjt_s.Index() > nljjt_r.Index()) {
            continue;
          }
          // r, s <= p, q (part 2)
          if ((nljjt_r.Index() == nljjt_p.Index()) &&
              (nljjt_s.Index() > nljjt_q.Index())) {
            continue;
          }
          // parity
          if (nljjt_p.P() + nljjt_q.P() != nljjt_r.P() + nljjt_s.P()) {
            continue;
          }
          // isospin
          if (nljjt_p.M_TT() + nljjt_q.M_TT() !=
              nljjt_r.M_TT() + nljjt_s.M_TT()) {
            continue;
          }
          const auto jj_pq_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_pq_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_rs_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_rs_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_2_min = std::max(jj_pq_min, jj_rs_min);
          const auto jj_2_max = std::min(jj_pq_max, jj_rs_max);

          if (jj_2_min <= jj_2_max) {
            counter += 1;
          }
        }
      }
    }
  }

  return counter;
}

absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t> MakeME2JPIndexLookup(
    imsrg::HOEnergy emax) {
  absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t> me_lookup;
  me_lookup.reserve(GetME2JPSize_NoJJ(emax));

  const auto basis = imsrg::mexj::GetNLJJTs(emax);

  std::size_t index = 0;
  for (const auto& nljjt_p : basis) {
    for (const auto& nljjt_q : basis) {
      // q <= p
      if (nljjt_q.Index() > nljjt_p.Index()) {
        continue;
      }
      for (const auto& nljjt_r : basis) {
        // r, s <= p, q (part 1)
        if (nljjt_r.Index() > nljjt_p.Index()) {
          continue;
        }
        for (const auto& nljjt_s : basis) {
          // s <= r
          if (nljjt_s.Index() > nljjt_r.Index()) {
            continue;
          }
          // r, s <= p, q (part 2)
          if ((nljjt_r.Index() == nljjt_p.Index()) &&
              (nljjt_s.Index() > nljjt_q.Index())) {
            continue;
          }
          // parity
          if (nljjt_p.P() + nljjt_q.P() != nljjt_r.P() + nljjt_s.P()) {
            continue;
          }
          // isospin
          if (nljjt_p.M_TT() + nljjt_q.M_TT() !=
              nljjt_r.M_TT() + nljjt_s.M_TT()) {
            continue;
          }
          const auto jj_pq_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_pq_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_p.JJ(), nljjt_q.JJ());
          const auto jj_rs_min = imsrg::CouplingMinimum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_rs_max = imsrg::CouplingMaximum<imsrg::TotalAngMom>(
              nljjt_r.JJ(), nljjt_s.JJ());
          const auto jj_2_min = std::max(jj_pq_min, jj_rs_min);
          const auto jj_2_max = std::min(jj_pq_max, jj_rs_max);

          const auto range_size =
              imsrg::CouplingRangeFromMinAndMax<imsrg::TotalAngMom>(jj_2_min,
                                                                    jj_2_max)
                  .size();

          if (range_size > 0) {
            imsrg::mexj::NLJJTIndex4 lookup_key(
                nljjt_p.Index(), nljjt_q.Index(), nljjt_r.Index(),
                nljjt_s.Index());
            me_lookup[lookup_key] = index;
            index += range_size;
          }
        }
      }
    }
  }

  return me_lookup;
}

template <typename S>
std::vector<double> ReadFile(S&& stream, HOEnergy emax) {
  // Process header
  std::string header;
  std::getline(stream, header);
  {
    const auto [valid_header, msg] = ValidateHeader(header);
    imsrg::CheckForError(!valid_header, msg);
  }

  // Read 2B MEs
  const auto size = GetME2JPSize(emax);
  std::vector<double> mes(size, 0.0);
  for (std::size_t i = 0; i < size; i += 1) {
    stream >> mes[i];
  }

  return mes;
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

  double me_2b;
  const auto size = GetME2JPSize(emax);
  for (std::size_t i = 0; i < size; i += 1) {
    stream >> me_2b;
    if (!stream) {
      return {false,
              fmt::format(
                  "Reached end of ME2JP file before two-body matrix element {} "
                  "was read.",
                  i)};
    }
  }

  // Will not check for file too long.
  // This makes it possible to read from larger emax file.

  return {true};
}

imsrg::ValidationResult ValidateHeader(std::string_view header) {
  if (header.find("me2jp") == std::string::npos) {
    // me2jp substring was not found, so header is invalid
    return {false, fmt::format("Header \"{}\" is invalid for ME2JP.", header)};
  }
  return {true};
}

}  // namespace detail

}  // namespace imsrg
