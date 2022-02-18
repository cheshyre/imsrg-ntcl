// Copyright 2022 Matthias Heinz
#ifndef IMSRG_FILES_FORMATS_HELPERS_MEXJ_H_
#define IMSRG_FILES_FORMATS_HELPERS_MEXJ_H_

#include <utility>
#include <vector>

#include "imsrg/model_space/single_particle/state.h"
#include "imsrg/quantum_numbers/ho_energy.h"
#include "imsrg/quantum_numbers/isospin_projection.h"
#include "imsrg/quantum_numbers/orbital_ang_mom.h"
#include "imsrg/quantum_numbers/parity.h"
#include "imsrg/quantum_numbers/radial_excitation_number.h"
#include "imsrg/quantum_numbers/total_ang_mom.h"

namespace imsrg {

namespace mexj {
// Safe up to emax = 30
const std::size_t kMEXJIndexFoldFactor = 1024;
const std::size_t kMEXJIndexFoldFactor2 =
    kMEXJIndexFoldFactor * kMEXJIndexFoldFactor;
const std::size_t kMEXJIndexFoldFactor3 =
    kMEXJIndexFoldFactor2 * kMEXJIndexFoldFactor;
const std::size_t kMEXJIndexFoldFactor4 =
    kMEXJIndexFoldFactor3 * kMEXJIndexFoldFactor;
const std::size_t kMEXJIndexFoldFactor5 =
    kMEXJIndexFoldFactor4 * kMEXJIndexFoldFactor;

class NLJJTIndex {
 public:
  explicit NLJJTIndex(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                      imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;

  static std::size_t ComputeIndex(imsrg::RadialExcitationNumber n,
                                  imsrg::OrbitalAngMom l, imsrg::TotalAngMom jj,
                                  imsrg::IsospinProj m_tt);
};
inline void swap(NLJJTIndex& a, NLJJTIndex& b) noexcept { a.swap(b); }
inline bool operator<=(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() <= b.AsSizeT();
}
inline bool operator<(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() < b.AsSizeT();
}
inline bool operator>(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() > b.AsSizeT();
}
inline bool operator>=(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() >= b.AsSizeT();
}
inline bool operator==(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() == b.AsSizeT();
}
inline bool operator!=(const NLJJTIndex& a, const NLJJTIndex& b) {
  return a.AsSizeT() != b.AsSizeT();
}

class NLJJT {
 public:
  explicit NLJJT(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                 imsrg::TotalAngMom jj, imsrg::IsospinProj m_tt);

  explicit NLJJT(const imsrg::SPState& s)
      : NLJJT(s.RadialN(), s.L(), s.JJ(), s.M_TT()) {}

  NLJJTIndex Index() const { return index_; }
  imsrg::TotalAngMom JJ() const { return jj_; }
  imsrg::Parity P() const { return l_.Parity(); }
  imsrg::IsospinProj M_TT() const { return m_tt_; }

  void swap(NLJJT& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
    swap(l_, other.l_);
    swap(jj_, other.jj_);
    swap(m_tt_, other.m_tt_);
    swap(index_, other.index_);
  }

 private:
  imsrg::RadialExcitationNumber n_;
  imsrg::OrbitalAngMom l_;
  imsrg::TotalAngMom jj_;
  imsrg::IsospinProj m_tt_;
  NLJJTIndex index_;
};
inline void swap(NLJJT& a, NLJJT& b) noexcept { a.swap(b); }

class NLJJIndex {
 public:
  explicit NLJJIndex(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                     imsrg::TotalAngMom jj);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;

  static std::size_t ComputeIndex(imsrg::RadialExcitationNumber n,
                                  imsrg::OrbitalAngMom l,
                                  imsrg::TotalAngMom jj);
};
inline void swap(NLJJIndex& a, NLJJIndex& b) noexcept { a.swap(b); }
inline bool operator<=(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() <= b.AsSizeT();
}
inline bool operator<(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() < b.AsSizeT();
}
inline bool operator>(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() > b.AsSizeT();
}
inline bool operator>=(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() >= b.AsSizeT();
}
inline bool operator==(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() == b.AsSizeT();
}
inline bool operator!=(const NLJJIndex& a, const NLJJIndex& b) {
  return a.AsSizeT() != b.AsSizeT();
}

class NLJJ {
 public:
  explicit NLJJ(imsrg::RadialExcitationNumber n, imsrg::OrbitalAngMom l,
                imsrg::TotalAngMom jj);
  explicit NLJJ(const imsrg::SPState& s) : NLJJ(s.RadialN(), s.L(), s.JJ()) {}

  NLJJIndex Index() const { return index_; }
  imsrg::TotalAngMom JJ() const { return jj_; }
  imsrg::Parity P() const { return l_.Parity(); }

  void swap(NLJJ& other) noexcept {
    using std::swap;
    swap(n_, other.n_);
    swap(l_, other.l_);
    swap(jj_, other.jj_);
    swap(index_, other.index_);
  }

 private:
  imsrg::RadialExcitationNumber n_;
  imsrg::OrbitalAngMom l_;
  imsrg::TotalAngMom jj_;
  NLJJIndex index_;
};
inline void swap(NLJJ& a, NLJJ& b) noexcept { a.swap(b); }

std::vector<NLJJT> GetNLJJTs(imsrg::HOEnergy emax);
std::vector<NLJJ> GetNLJJs(imsrg::HOEnergy emax);

class NLJJTIndex2 {
 public:
  explicit NLJJTIndex2(NLJJTIndex i1, NLJJTIndex i2);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex2& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex2& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJTIndex2& a, NLJJTIndex2& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJTIndex2& a, const NLJJTIndex2& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJTIndex3 {
 public:
  explicit NLJJTIndex3(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex3& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex3& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJTIndex3& a, NLJJTIndex3& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJTIndex3& a, const NLJJTIndex3& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJTIndex4 {
 public:
  explicit NLJJTIndex4(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                       NLJJTIndex i4);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex4& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex4& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJTIndex4& a, NLJJTIndex4& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJTIndex4& a, const NLJJTIndex4& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJTIndex5 {
 public:
  explicit NLJJTIndex5(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                       NLJJTIndex i4, NLJJTIndex i5);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex5& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex5& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJTIndex5& a, NLJJTIndex5& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJTIndex5& a, const NLJJTIndex5& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJTIndex6 {
 public:
  explicit NLJJTIndex6(NLJJTIndex i1, NLJJTIndex i2, NLJJTIndex i3,
                       NLJJTIndex i4, NLJJTIndex i5, NLJJTIndex i6);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJTIndex6& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJTIndex6& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJTIndex6& a, NLJJTIndex6& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJTIndex6& a, const NLJJTIndex6& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJIndex2 {
 public:
  explicit NLJJIndex2(NLJJIndex i1, NLJJIndex i2);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex2& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex2& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJIndex2& a, NLJJIndex2& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJIndex2& a, const NLJJIndex2& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJIndex3 {
 public:
  explicit NLJJIndex3(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex3& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex3& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJIndex3& a, NLJJIndex3& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJIndex3& a, const NLJJIndex3& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJIndex4 {
 public:
  explicit NLJJIndex4(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex4& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex4& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJIndex4& a, NLJJIndex4& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJIndex4& a, const NLJJIndex4& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJIndex5 {
 public:
  explicit NLJJIndex5(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4,
                      NLJJIndex i5);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex5& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex5& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJIndex5& a, NLJJIndex5& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJIndex5& a, const NLJJIndex5& b) {
  return a.AsSizeT() == b.AsSizeT();
}

class NLJJIndex6 {
 public:
  explicit NLJJIndex6(NLJJIndex i1, NLJJIndex i2, NLJJIndex i3, NLJJIndex i4,
                      NLJJIndex i5, NLJJIndex i6);

  std::size_t AsSizeT() const { return index_; }

  template <typename H>
  friend H AbslHashValue(H h, const NLJJIndex6& o) {
    return H::combine(std::move(h), o.index_);
  }

  void swap(NLJJIndex6& other) noexcept {
    using std::swap;
    swap(index_, other.index_);
  }

 private:
  std::size_t index_;
};
inline void swap(NLJJIndex6& a, NLJJIndex6& b) noexcept { a.swap(b); }
inline bool operator==(const NLJJIndex6& a, const NLJJIndex6& b) {
  return a.AsSizeT() == b.AsSizeT();
}

}  // namespace mexj

}  // namespace imsrg

#endif  // IMSRG_FILES_FORMATS_HELPERS_MEXJ_H_
