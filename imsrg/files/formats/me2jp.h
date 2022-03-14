// Copyright 2022 Matthias Heinz
#ifndef IMSRG_FILES_FORMATS_ME2JP_H_
#define IMSRG_FILES_FORMATS_ME2JP_H_

#include <string>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_map.h"

#include "imsrg/files/formats/helpers/mexj.h"
#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/hermiticity.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {
class ME2JPFile {
 public:
  static ME2JPFile FromTextFile(std::string path_to_file, HOEnergy emax,
                                Hermiticity herm);
  static ME2JPFile FromGZippedFile(std::string path_to_file, HOEnergy emax,
                                   Hermiticity herm) = delete;
  static ME2JPFile FromBinary(std::string path_to_file, HOEnergy emax,
                              Hermiticity herm) = delete;

  double Get2BMatrixElement(const SPState& p, const SPState& q,
                            const SPState& r, const SPState& s,
                            TotalAngMom jj_2b) const;
  Hermiticity Herm() const { return herm_; }

  void swap(ME2JPFile& other) noexcept {
    using std::swap;
    swap(herm_, other.herm_);
    swap(mes_, other.mes_);
    swap(me_lookup_, other.me_lookup_);
  }

 private:
  Hermiticity herm_;
  std::vector<double> mes_;
  absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t> me_lookup_;

  explicit ME2JPFile(
      Hermiticity herm, std::vector<double>&& mes,
      absl::flat_hash_map<imsrg::mexj::NLJJTIndex4, std::size_t>&& me_lookup);
};

inline void swap(ME2JPFile& a, ME2JPFile& b) noexcept { a.swap(b); }

}  // namespace imsrg
#endif  // IMSRG_FILES_FORMATS_ME2JP_H_
