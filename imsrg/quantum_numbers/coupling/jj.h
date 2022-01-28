// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_JJ_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_JJ_H_

#include <utility>

#include "lib/GSL/include/gsl/assert"

namespace imsrg {
class JJ {
 private:
  int jj_;

 public:
  /**
   * @brief Construct new JJ (2 * j, where j is angular momentum) from integer.
   *
   * @param jj
   */
  explicit JJ(int jj) : jj_(jj) { Expects(jj >= 0); }

  // Default copy, move, and destructor

  int AsInt() const { return jj_; }

  void swap(JJ& other) noexcept {
    using std::swap;
    swap(jj_, other.jj_);
  }
};

inline void swap(JJ& a, JJ& b) noexcept { a.swap(b); }
inline bool operator<(JJ a, JJ b) { return a.AsInt() < b.AsInt(); }
inline bool operator==(JJ a, JJ b) { return a.AsInt() == b.AsInt(); }
inline bool operator<=(JJ a, JJ b) { return a.AsInt() <= b.AsInt(); }
inline bool operator>(JJ a, JJ b) { return a.AsInt() > b.AsInt(); }
inline bool operator!=(JJ a, JJ b) { return a.AsInt() != b.AsInt(); }
inline bool operator>=(JJ a, JJ b) { return a.AsInt() >= b.AsInt(); }

}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_JJ_H_