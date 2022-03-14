// Copyright 2022 Matthias Heinz
#ifndef IMSRG_OPERATOR_SCALAR_ONE_BODY_OPERATOR_H_
#define IMSRG_OPERATOR_SCALAR_ONE_BODY_OPERATOR_H_

#include <memory>
#include <utility>
#include <vector>

#include "ntcl/data/f_array.h"

#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

class Scalar1BOperator {
 public:
  static Scalar1BOperator FromScalar1BModelSpace(
      const std::shared_ptr<const Scalar1BModelSpace>& ms_ptr,
      Hermiticity herm);

  // Default copy, move, and dtor

  Hermiticity Herm() const { return herm_; }

  std::size_t size() const { return tensors_.size(); }

  const ntcl::FArray<double, 2>& GetTensorAtIndex(std::size_t i) const {
    return tensors_[i];
  }

  // This is an unsafe handle to an internal object in this operator.
  // The only mutable operation supported is the setting of tensor elements,
  // i.e.: a(i, j) = 2.0; Furthermore, this is not a thread-safe operation in
  // the sense that 2 threads should not write to the same matrix element at
  // once. It is up to the user to guarantee this.
  ntcl::FArray<double, 2>& GetMutableTensorAtIndex(std::size_t i) {
    return tensors_[i];
  }
  const Scalar1BModelSpace& GetModelSpace() const { return *ms_ptr_; }
  std::shared_ptr<const Scalar1BModelSpace> GetModelSpacePtr() const {
    return ms_ptr_;
  }

  void swap(Scalar1BOperator& other) noexcept {
    using std::swap;
    swap(ms_ptr_, other.ms_ptr_);
    swap(herm_, other.herm_);
    swap(tensors_, other.tensors_);
  }

 private:
  std::shared_ptr<const Scalar1BModelSpace> ms_ptr_;
  Hermiticity herm_;
  std::vector<ntcl::FArray<double, 2>> tensors_;

  explicit Scalar1BOperator(
      const std::shared_ptr<const Scalar1BModelSpace>& ms_ptr, Hermiticity herm,
      std::vector<ntcl::FArray<double, 2>>&& tensors);
};

inline void swap(Scalar1BOperator& a, Scalar1BOperator& b) noexcept {
  a.swap(b);
}

}  // namespace imsrg

#endif  // IMSRG_OPERATOR_SCALAR_ONE_BODY_OPERATOR_H_
