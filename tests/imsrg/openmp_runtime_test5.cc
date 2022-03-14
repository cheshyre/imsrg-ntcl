// Copyright 2022 Matthias Heinz
// Do not merge with other openmp_runtime_test files.
// Because of singleton nature of OpenMPRuntime,
// these tests need to be run truly independently (in separate executables).
#include "imsrg/openmp_runtime.h"

#include <omp.h>

#include <vector>

#include "tests/catch.hpp"

static const std::size_t kTestArraySize = 1000;

TEST_CASE("Test 2 thread initialize.") {
  using imsrg::OpenMPRuntime;

  const int num_threads = 2;

  REQUIRE_FALSE(OpenMPRuntime::IsInitialized());

  const auto& runtime = OpenMPRuntime::InitializeRuntime(num_threads);

  REQUIRE(OpenMPRuntime::IsInitialized());

  const auto& runtime2 = OpenMPRuntime::GetInstance();

  REQUIRE(OpenMPRuntime::IsInitialized());

  (void)runtime;

  std::vector<bool> max_thread_value_checks(kTestArraySize, false);
  std::vector<bool> thread_id_checks(kTestArraySize, false);
  std::vector<bool> parallel_region_checks(kTestArraySize, false);
  std::vector<bool> num_thread_value_checks(kTestArraySize, false);

  SECTION("using runtime from GetInstance") {
    REQUIRE_FALSE(runtime2.InParallelRegion());

#pragma omp parallel for
    for (std::size_t i = 0; i < kTestArraySize; i++) {
      max_thread_value_checks[i] =
          omp_get_num_threads() == runtime2.MaxNumberOfThreads();
      thread_id_checks[i] = omp_get_thread_num() == runtime2.ThreadId();
      parallel_region_checks[i] = runtime2.InParallelRegion();
      num_thread_value_checks[i] =
          (num_threads == runtime2.MaxNumberOfThreads());
    }

    REQUIRE_FALSE(runtime2.InParallelRegion());
  }

  for (std::size_t i = 0; i < kTestArraySize; i++) {
    INFO("i = " << i);
    REQUIRE(max_thread_value_checks[i]);
    REQUIRE(thread_id_checks[i]);
    REQUIRE(parallel_region_checks[i]);
    REQUIRE(num_thread_value_checks[i]);
  }
}
