// Copyright 2022 Matthias Heinz
// Do not merge with other openmp_runtime_test files.
// Because of singleton nature of OpenMPRuntime,
// these tests need to be run truly independently (in separate executables).
#include "imsrg/openmp_runtime.h"

#include <omp.h>

#include <vector>

#include "tests/catch.hpp"

TEST_CASE("Test GetInstance before Initialized.", "[!hide][!shouldfail]") {
  using imsrg::OpenMPRuntime;

  const auto& runtime2 = OpenMPRuntime::GetInstance();

  REQUIRE(!OpenMPRuntime::IsInitialized());

  (void)runtime2;
}
