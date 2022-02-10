// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"

#include <cmath>
#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

std::vector<imsrg::JJ> GenerateCouplingRange(JJ a, JJ b) {
  imsrg::JJ min_jj(std::abs(a.AsInt() - b.AsInt()));
  imsrg::JJ max_jj(a.AsInt() + b.AsInt());

  std::vector<imsrg::JJ> jjs;
  jjs.reserve((max_jj.AsInt() - min_jj.AsInt()) / 2 + 1);
  for (int jj_i = min_jj.AsInt(); jj_i <= max_jj.AsInt(); jj_i += 2) {
    jjs.push_back(imsrg::JJ(jj_i));
  }

  return jjs;
}

}  // namespace imsrg
