// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_

#include <vector>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

std::vector<imsrg::JJ> GenerateCouplingRange(JJ a, JJ b);
JJ CouplingMinimum(JJ a, JJ b);
JJ CouplingMaximum(JJ a, JJ b);
std::vector<imsrg::JJ> CouplingRangeFromMinAndMax(JJ min, JJ max);

template <typename T3, typename T1, typename T2>
std::vector<T3> GenerateCouplingRange(T1 a, T2 b) {
  std::vector<imsrg::JJ> jjs = GenerateCouplingRange(a.AsJJ(), b.AsJJ());
  return std::vector<T3>(jjs.begin(), jjs.end());
}

template <typename T3, typename T1, typename T2>
T3 CouplingMinimum(T1 a, T2 b) {
  return T3(CouplingMinimum(a.AsJJ(), b.AsJJ()));
}

template <typename T3, typename T1, typename T2>
T3 CouplingMaximum(T1 a, T2 b) {
  return T3(CouplingMaximum(a.AsJJ(), b.AsJJ()));
}

template <typename T>
std::vector<T> CouplingRangeFromMinAndMax(T min, T max) {
  std::vector<imsrg::JJ> jjs =
      CouplingRangeFromMinAndMax(min.AsJJ(), max.AsJJ());
  return std::vector<T>(jjs.begin(), jjs.end());
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_COUPLING_RANGES_H_
