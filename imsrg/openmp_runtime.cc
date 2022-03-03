// Copyright 2022 Matthias Heinz
#include "imsrg/openmp_runtime.h"

#include <omp.h>

#include "imsrg/assert.h"

namespace imsrg {

const OpenMPRuntime& OpenMPRuntime::GetInstance() {
  const auto& instance = GetMutableInstance();
  Expects(instance.Initialized());
  return instance;
}

bool OpenMPRuntime::IsInitialized() {
  const auto& instance = GetMutableInstance();
  return instance.Initialized();
}

const OpenMPRuntime& OpenMPRuntime::InitializeRuntime() {
  auto& instance = OpenMPRuntime::GetMutableInstance();
  Expects(!instance.Initialized());
  instance.Init();
  return instance;
}

const OpenMPRuntime& OpenMPRuntime::InitializeRuntime(
    int max_number_of_threads) {
  auto& instance = OpenMPRuntime::GetMutableInstance();
  Expects(!instance.Initialized());
  instance.Init(max_number_of_threads);
  return instance;
}

int OpenMPRuntime::ThreadId() const { return omp_get_thread_num(); }

bool OpenMPRuntime::InParallelRegion() const { return omp_in_parallel(); }

OpenMPRuntime& OpenMPRuntime::GetMutableInstance() {
  static OpenMPRuntime instance;
  return instance;
}

OpenMPRuntime::OpenMPRuntime() {}

void OpenMPRuntime::Init() {
  int num_threads = 1;
#pragma omp parallel
  {
#pragma omp critical(num_threads)
    { num_threads = omp_get_num_threads(); }
  }
  max_number_of_threads_ = num_threads;
  init_ = true;
}

void OpenMPRuntime::Init(int max_number_of_threads) {
  omp_set_num_threads(max_number_of_threads);
  max_number_of_threads_ = max_number_of_threads;
  init_ = true;
}

}  // namespace imsrg
