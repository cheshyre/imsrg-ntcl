// Copyright 2022 Matthias Heinz
#ifndef TESTS_HELPERS_EQUALITY_H_
#define TESTS_HELPERS_EQUALITY_H_

#include <vector>

namespace imsrg {
namespace test {

template <typename T>
bool AreVectorsEqual(const std::vector<T>& a, const std::vector<T>& b) {
  if (a.size() != b.size()) {
    return false;
  }

  for (std::size_t i = 0; i < a.size(); i++) {
    if (!(a[i] == b[i])) {
      return false;
    }
  }

  return true;
}

}  // namespace test
}  // namespace imsrg

#endif  // TESTS_HELPERS_EQUALITY_H_
