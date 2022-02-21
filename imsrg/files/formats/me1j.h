// Copyright 2022 Matthias Heinz
#ifndef IMSRG_FILES_FORMATS_ME1J_H_
#define IMSRG_FILES_FORMATS_ME1J_H_

#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/files/formats/helpers/mexj.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"

namespace imsrg {
class ME1JFile {
 public:
  static ME1JFile FromTextFile(std::string path_to_file, HOEnergy emax,
                               Hermiticity herm);
  static ME1JFile FromGZippedFile(std::string path_to_file, HOEnergy emax,
                                  Hermiticity herm) = delete;
  static ME1JFile FromBinary(std::string path_to_file, HOEnergy emax,
                             Hermiticity herm) = delete;

  double Get0BPart() const { return me_0b_; }
  double Get1BMatrixElement(const SPState& p, const SPState& q) const;
  Hermiticity Herm() const { return herm_; }

  void swap(ME1JFile& other) noexcept {
    using std::swap;
    swap(me_0b_, other.me_0b_);
    swap(herm_, other.herm_);
    swap(mes_, other.mes_);
    swap(me_lookup_, other.me_lookup_);
  }

 private:
  double me_0b_;
  Hermiticity herm_;
  std::vector<double> mes_;
  absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t> me_lookup_;

  explicit ME1JFile(
      double me_0b, Hermiticity herm, std::vector<double>&& mes,
      absl::flat_hash_map<imsrg::mexj::NLJJTIndex2, std::size_t>&& me_lookup);
};

inline void swap(ME1JFile& a, ME1JFile& b) noexcept { a.swap(b); }

}  // namespace imsrg

#endif  // IMSRG_FILES_FORMATS_ME1J_H_
