// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_

#include <cmath>
#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

inline std::vector<imsrg::JJ> GenerateCouplingRange(JJ a, JJ b) {
  imsrg::JJ min_jj(std::abs(a.AsInt() - b.AsInt()));
  imsrg::JJ max_jj(a.AsInt() + b.AsInt());

  std::vector<imsrg::JJ> jjs;
  jjs.reserve((max_jj.AsInt() - min_jj.AsInt()) / 2 + 1);
  for (int jj_i = min_jj.AsInt(); jj_i <= max_jj.AsInt(); jj_i += 2) {
    jjs.push_back(imsrg::JJ(jj_i));
  }

  return jjs;
}

template <typename T3, typename T1, typename T2>
std::vector<T3> GenerateCouplingRange(T1 a, T2 b) {
  std::vector<imsrg::JJ> jjs = GenerateCouplingRange(a.AsJJ(), b.AsJJ());
  return std::vector<T3>(jjs.begin(), jjs.end());
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
