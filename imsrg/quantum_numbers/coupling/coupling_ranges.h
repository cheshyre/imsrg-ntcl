// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_

#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

std::vector<imsrg::JJ> GenerateCouplingRange(JJ a, JJ b);

template <typename T3, typename T1, typename T2>
std::vector<T3> GenerateCouplingRange(T1 a, T2 b) {
  std::vector<imsrg::JJ> jjs = GenerateCouplingRange(a.AsJJ(), b.AsJJ());
  return std::vector<T3>(jjs.begin(), jjs.end());
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
