// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPENMP_RUNTIME_H_
#define IMSRG_OPENMP_RUNTIME_H_

namespace imsrg {

class OpenMPRuntime {
 public:
  static const OpenMPRuntime& GetInstance();
  static bool IsInitialized();
  static const OpenMPRuntime& InitializeRuntime();
  static const OpenMPRuntime& InitializeRuntime(int max_number_of_threads);

  OpenMPRuntime(const OpenMPRuntime&) = delete;
  OpenMPRuntime& operator=(const OpenMPRuntime&) = delete;

  int MaxNumberOfThreads() const { return max_number_of_threads_; }
  int ThreadId() const;
  bool InParallelRegion() const;

 private:
  static OpenMPRuntime& GetMutableInstance();

  OpenMPRuntime();

  void Init();
  void Init(int max_number_of_threads);

  bool Initialized() const { return init_; }

  bool init_ = false;
  int max_number_of_threads_ = 1;
};
}  // namespace imsrg

#endif  // IMSRG_OPENMP_RUNTIME_H_
