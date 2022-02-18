// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_FACTORS_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_FACTORS_H_

#include <cmath>

#include "imsrg/quantum_numbers/coupling/jj.h"

namespace imsrg {

inline double Hat(JJ jj) { return std::sqrt(jj.AsInt() + 1); }

inline int HatSquared(JJ jj) { return jj.AsInt() + 1; }

template <typename T>
double Hat(T jj) {
  return Hat(jj.AsJJ());
}

template <typename T>
double HatSquared(T jj) {
  return HatSquared(jj.AsJJ());
}

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_FACTORS_H_
