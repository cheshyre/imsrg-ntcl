// Copyright 2022 Matthias Heinz
#ifndef IMSRG_ERROR_H_
#define IMSRG_ERROR_H_

#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "spdlog/spdlog.h"

namespace imsrg {

struct ValidationResult {
  bool valid = true;
  std::string first_err_msg = "";
};
inline void swap(ValidationResult& a, ValidationResult& b) noexcept {
  using std::swap;
  swap(a.valid, b.valid);
  swap(a.first_err_msg, b.first_err_msg);
}

class GeneralError : public std::runtime_error {
  // Inherit constructor
  using std::runtime_error::runtime_error;
};

inline void Error(std::string_view msg) {
  spdlog::error(msg);
  throw imsrg::GeneralError(std::string(msg));
}

// True value for fail will log an error and raise an exception
inline void CheckForError(bool fail, std::string_view msg) {
  if (fail) {
    Error(msg);
  }
}

}  // namespace imsrg

#endif  // IMSRG_ERROR_H_
