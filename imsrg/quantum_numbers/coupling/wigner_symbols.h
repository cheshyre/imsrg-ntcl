// Copyright 2022 Matthias Heinz
#ifndef IMSRG_QUANTUM_NUMBERS_COUPLING_WIGNER_SYMBOLS_H_
#define IMSRG_QUANTUM_NUMBERS_COUPLING_WIGNER_SYMBOLS_H_

#include "imsrg/quantum_numbers/coupling/jj.h"
#include "imsrg/quantum_numbers/coupling/m_jj.h"

namespace imsrg {

const int kMaxJJ = 100;

class WignerSymbolEngine {
 public:
  static const WignerSymbolEngine& GetInstance();

  WignerSymbolEngine(const WignerSymbolEngine&) = delete;
  WignerSymbolEngine operator=(const WignerSymbolEngine&) = delete;

  double Wigner3J(imsrg::JJ jj1, imsrg::JJ jj2, imsrg::JJ jj3,
                  imsrg::M_JJ m_jj1, imsrg::M_JJ m_jj2,
                  imsrg::M_JJ m_jj3) const;

  double ClebschGordan(imsrg::JJ jj1, imsrg::JJ jj2, imsrg::JJ jj3,
                       imsrg::M_JJ m_jj1, imsrg::M_JJ m_jj2,
                       imsrg::M_JJ m_jj3) const;

  double Wigner6J(imsrg::JJ jj1, imsrg::JJ jj2, imsrg::JJ jj3, imsrg::JJ jj4,
                  imsrg::JJ jj5, imsrg::JJ jj6) const;

 private:
  bool thread_safe_ = false;

  WignerSymbolEngine();
  ~WignerSymbolEngine();
};
}  // namespace imsrg

#endif  // IMSRG_QUANTUM_NUMBERS_COUPLING_WIGNER_SYMBOLS_H_
