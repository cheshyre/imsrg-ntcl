// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPERATOR_SCALAR_TWO_BODY_OPERATOR_H_
#define IMSRG_OPERATOR_SCALAR_TWO_BODY_OPERATOR_H_

#include <memory>
#include <utility>
#include <vector>

#include "ntcl/data/f_array.h"

#include "imsrg/model_space/scalar/two_body/model_space.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

class Scalar2BOperator {
 public:
  static Scalar2BOperator FromScalar2BModelSpace(
      const std::shared_ptr<const Scalar2BModelSpace>& ms_ptr,
      Hermiticity herm);

  Hermiticity Herm() const { return herm_; }

  std::size_t size() const { return tensors_.size(); }

  const ntcl::FArray<double, 4>& GetTensorAtIndex(std::size_t i) const {
    return tensors_[i];
  }

  // This is an unsafe handle to an internal object in this operator.
  // The only mutable operation supported is the setting of tensor elements,
  // i.e.: a(i, j, k, l) = 2.0; Furthermore, this is not a thread-safe operation
  // in the sense that 2 threads should not write to the same matrix element at
  // once. It is up to the user to guarantee this.
  ntcl::FArray<double, 4>& GetMutableTensorAtIndex(std::size_t i) {
    return tensors_[i];
  }
  const Scalar2BModelSpace& GetModelSpace() const { return *ms_ptr_; }
  std::shared_ptr<const Scalar2BModelSpace> GetModelSpacePtr() const {
    return ms_ptr_;
  }

  void swap(Scalar2BOperator& other) noexcept {
    using std::swap;
    swap(ms_ptr_, other.ms_ptr_);
    swap(herm_, other.herm_);
    swap(tensors_, other.tensors_);
  }

 private:
  std::shared_ptr<const Scalar2BModelSpace> ms_ptr_;
  Hermiticity herm_;
  std::vector<ntcl::FArray<double, 4>> tensors_;

  explicit Scalar2BOperator(
      const std::shared_ptr<const Scalar2BModelSpace>& ms_ptr, Hermiticity herm,
      std::vector<ntcl::FArray<double, 4>>&& tensors);
};

inline void swap(Scalar2BOperator& a, Scalar2BOperator& b) noexcept {
  a.swap(b);
}

}  // namespace imsrg

#endif  // IMSRG_OPERATOR_SCALAR_TWO_BODY_OPERATOR_H_
