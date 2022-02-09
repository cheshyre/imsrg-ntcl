// Copyright 2022 Matthias Heinz
#ifndef IMSRG_ASSERT_H_
#define IMSRG_ASSERT_H_

#include <stdexcept>

#include "fmt/core.h"
#include "spdlog/spdlog.h"

#define Expects(x) imsrg::detail::CheckPrecondition(x, __FILE__, __LINE__, #x)
#define Ensures(x) imsrg::detail::CheckPostcondition(x, __FILE__, __LINE__, #x)

namespace imsrg {

constexpr bool kRuntimePreconditionCheck = true;
constexpr bool kRuntimePostconditionCheck = true;

class PreconditionError : public std::logic_error {
  // Inherit constructor
  using std::logic_error::logic_error;
};
class PostconditionError : public std::logic_error {
  // Inherit constructor
  using std::logic_error::logic_error;
};

namespace detail {

inline void CheckPrecondition(bool val, const char* file, int line,
                              const char* assertion) {
  if constexpr (imsrg::kRuntimePreconditionCheck) {
    if (!val) {
      spdlog::error("Precondition failed ({}:{}): {}", file, line, assertion);
      throw imsrg::PreconditionError(fmt::format(
          "Precondition failed ({}:{}): {}", file, line, assertion));
    }
  }
}

inline void CheckPostcondition(bool val, const char* file, int line,
                               const char* assertion) {
  if constexpr (imsrg::kRuntimePostconditionCheck) {
    if (!val) {
      spdlog::error("Postcondition failed ({}:{}): {}", file, line, assertion);
      throw imsrg::PostconditionError(fmt::format(
          "Postcondition failed ({}:{}): {}", file, line, assertion));
    }
  }
}
}  // namespace detail

}  // namespace imsrg

#endif  // IMSRG_ASSERT_H_
