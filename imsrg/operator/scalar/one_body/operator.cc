// Copyright 2022 Matthias Heinz
#include "imsrg/operator/scalar/one_body/operator.h"

#include <memory>
#include <utility>
#include <vector>

#include "ntcl/data/f_array.h"

#include "imsrg/assert.h"
#include "imsrg/model_space/scalar/one_body/model_space.h"
#include "imsrg/quantum_numbers/hermiticity.h"

namespace imsrg {

Scalar1BOperator Scalar1BOperator::FromScalar1BModelSpace(
    const std::shared_ptr<const Scalar1BModelSpace>& ms_ptr, Hermiticity herm) {
  std::vector<ntcl::FArray<double, 2>> tensors;
  tensors.reserve(ms_ptr->NumberOfChannels());

  for (std::size_t index = 0; index < ms_ptr->size(); index++) {
    const auto& chan = ms_ptr->ChannelAtIndex(index);
    const auto& dim_i = chan.BraChannel().size();
    const auto& dim_j = chan.KetChannel().size();

    tensors.emplace_back(dim_i, dim_j);
  }

  Ensures(ms_ptr->NumberOfChannels() == tensors.size());

  return Scalar1BOperator(ms_ptr, herm, std::move(tensors));
}

Scalar1BOperator::Scalar1BOperator(
    const std::shared_ptr<const Scalar1BModelSpace>& ms_ptr, Hermiticity herm,
    std::vector<ntcl::FArray<double, 2>>&& tensors)
    : ms_ptr_(ms_ptr), herm_(herm), tensors_(std::move(tensors)) {
  Expects(ms_ptr_->NumberOfChannels() == tensors_.size());
}

}  // namespace imsrg
