// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/coupling_ranges.h"

#include <cmath>
#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

std::vector<imsrg::JJ> GenerateCouplingRange(JJ a, JJ b) {
  const auto min_jj = CouplingMinimum(a, b);
  const auto max_jj = CouplingMaximum(a, b);

  return CouplingRangeFromMinAndMax(min_jj, max_jj);
}

JJ CouplingMinimum(JJ a, JJ b) { return JJ(std::abs(a.AsInt() - b.AsInt())); }
JJ CouplingMaximum(JJ a, JJ b) { return JJ(a.AsInt() + b.AsInt()); }
std::vector<imsrg::JJ> CouplingRangeFromMinAndMax(JJ min, JJ max) {
  std::vector<imsrg::JJ> jjs;
  jjs.reserve((max.AsInt() - min.AsInt()) / 2 + 1);
  for (int jj_i = min.AsInt(); jj_i <= max.AsInt(); jj_i += 2) {
    jjs.push_back(imsrg::JJ(jj_i));
  }

  return jjs;
}

}  // namespace imsrg
