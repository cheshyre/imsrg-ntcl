// Copyright 2022 Matthias Heinz
#include "imsrg/quantum_numbers/coupling/wigner_symbols.h"

#include "spdlog/spdlog.h"
#include "wigxjpf.h"  // NOLINT(build/include_subdir)

#include "imsrg/assert.h"
#include "imsrg/openmp_runtime.h"
#include "imsrg/quantum_numbers/coupling/factors.h"
#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/m_jj.h"

namespace imsrg {

const WignerSymbolEngine& WignerSymbolEngine::GetInstance() {
  static WignerSymbolEngine instance;
  return instance;
}

double WignerSymbolEngine::Wigner3J(imsrg::JJ jj1, imsrg::JJ jj2, imsrg::JJ jj3,
                                    imsrg::M_JJ m_jj1, imsrg::M_JJ m_jj2,
                                    imsrg::M_JJ m_jj3) const {
  return wig3jj(jj1.AsInt(), jj2.AsInt(), jj3.AsInt(), m_jj1.AsInt(),
                m_jj2.AsInt(), m_jj3.AsInt());
}

double WignerSymbolEngine::ClebschGordan(imsrg::JJ jj1, imsrg::JJ jj2,
                                         imsrg::JJ jj3, imsrg::M_JJ m_jj1,
                                         imsrg::M_JJ m_jj2,
                                         imsrg::M_JJ m_jj3) const {
  return Hat(jj3) * (jj2.Phase() * jj1.Phase(-1) * m_jj3.Phase(-1)).AsInt() *
         Wigner3J(jj1, jj2, jj3, m_jj1, m_jj2, M_JJ(-1 * m_jj3.AsInt()));
}

double WignerSymbolEngine::Wigner6J(imsrg::JJ jj1, imsrg::JJ jj2, imsrg::JJ jj3,
                                    imsrg::JJ jj4, imsrg::JJ jj5,
                                    imsrg::JJ jj6) const {
  return wig6jj(jj1.AsInt(), jj2.AsInt(), jj3.AsInt(), jj4.AsInt(), jj5.AsInt(),
                jj6.AsInt());
}

WignerSymbolEngine::WignerSymbolEngine() {
  thread_safe_ = OpenMPRuntime::IsInitialized();
  wig_table_init(kMaxJJ, 9);
  if (thread_safe_) {
    Expects(!OpenMPRuntime::GetInstance().InParallelRegion());
#pragma omp parallel
    { wig_thread_temp_init(kMaxJJ); }
  } else {
    spdlog::warn(
        "OpenMPRuntime has not been initialized. Symbol evaluations will not "
        "be thread safe.");
    spdlog::warn(
        "To avoid this warning, evaluate OpenMP::InitializeRuntime() sometime "
        "before getting the engine for the first time.");
    wig_thread_temp_init(kMaxJJ);
  }
}

WignerSymbolEngine::~WignerSymbolEngine() {
  if (thread_safe_) {
#pragma omp parallel
    { wig_temp_free(); }
  } else {
    wig_temp_free();
  }
  wig_table_free();
}

}  // namespace imsrg
