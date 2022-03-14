// Copyright 2022 Matthias Heinz
#include "imsrg/commutator/scalar/comm_122.h"

#include <algorithm>
#include <vector>

#include "ntcl/algorithms/easy_tensor_contraction_interface_cbind.h"
#include "ntcl/data/f_array.h"

#include "imsrg/model_space/scalar/one_body/channel_key.h"
#include "imsrg/operator/scalar/one_body/operator.h"
#include "imsrg/operator/scalar/two_body/antisymmetry.h"

namespace imsrg {

namespace detail {

static void EvaluateScalar122CommutatorWithFactor(const Scalar1BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar2BOperator& c,
                                                  int factor);

static void EvaluateScalar122CommutatorRefImplWithFactor(
    const Scalar1BOperator& a, const Scalar2BOperator& b, Scalar2BOperator& c,
    int factor);

}  // namespace detail

void EvaluateScalar122Commutator(const Scalar1BOperator& a,
                                 const Scalar2BOperator& b,
                                 Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar122CommutatorWithFactor(a, b, c, 1);
}

void EvaluateScalar122CommutatorRefImpl(const Scalar1BOperator& a,
                                        const Scalar2BOperator& b,
                                        Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar122CommutatorRefImplWithFactor(a, b, c, 1);
}

void EvaluateScalar212Commutator(const Scalar2BOperator& a,
                                 const Scalar1BOperator& b,
                                 Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar122CommutatorWithFactor(b, a, c, -1);
}

void EvaluateScalar212CommutatorRefImpl(const Scalar2BOperator& a,
                                        const Scalar1BOperator& b,
                                        Scalar2BOperator& c) {
  imsrg::detail::EvaluateScalar122CommutatorRefImplWithFactor(b, a, c, -1);
}

namespace detail {

void EvaluateScalar122CommutatorWithFactor(const Scalar1BOperator& a,
                                           const Scalar2BOperator& b,
                                           Scalar2BOperator& c, int factor) {
  Expects(b.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  // const auto& ntcl_engine = ntcl::AlgorithmsEngine::GetInstance();

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    std::size_t chan_b_index = chan_c_index;

    const auto& chan_c = ms_2b.ChannelAtIndex(chan_c_index);
    const auto& chan_1 = chan_c.BraChannel1();
    const auto& chan_2 = chan_c.BraChannel2();
    const auto& chan_3 = chan_c.KetChannel1();
    const auto& chan_4 = chan_c.KetChannel2();

    imsrg::Scalar1BChannelKey chankey_a_1(chan_1.ChannelKey(),
                                          chan_1.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_2(chan_2.ChannelKey(),
                                          chan_2.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_3(chan_3.ChannelKey(),
                                          chan_3.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_4(chan_4.ChannelKey(),
                                          chan_4.ChannelKey());

    // We assume these are all in ms_1b
    // If they are not, it is a runtime error that will be detected
    // (assuming debugging is not turned off)
    const auto chan_a_1_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_1);
    const auto chan_a_2_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_2);
    const auto chan_a_3_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_3);
    const auto chan_a_4_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_4);

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);
    const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);
    const auto& tensor_a_1 = a.GetTensorAtIndex(chan_a_1_index);
    const auto& tensor_a_2 = a.GetTensorAtIndex(chan_a_2_index);
    const auto& tensor_a_3 = a.GetTensorAtIndex(chan_a_3_index);
    const auto& tensor_a_4 = a.GetTensorAtIndex(chan_a_4_index);

    // Dims
    const auto dim_1 = chan_1.size();
    const auto dim_2 = chan_2.size();
    const auto dim_3 = chan_3.size();
    const auto dim_4 = chan_4.size();

    // These tensors contractions do not seem to work.
    // ntcl_engine.Contract(tensor_c, tensor_a_1, tensor_b,
    //                      "C(i,j,k,l)=A(i,p)*B(p,j,k,l)", factor, 1.0);
    // ntcl_engine.Contract(tensor_c, tensor_a_2, tensor_b,
    //                      "C(i,j,k,l)=A(j,p)*B(i,p,k,l)", factor, 1.0);
    // ntcl_engine.Contract(tensor_c, tensor_a_3, tensor_b,
    //                      "C(i,j,k,l)=A(p,k)*B(i,j,p,l)", -1 * factor, 1.0);
    // ntcl_engine.Contract(tensor_c, tensor_a_4, tensor_b,
    //                      "C(i,j,k,l)=A(p,l)*B(i,j,k,p)", -1 * factor, 1.0);

    for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
      for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
        for (std::size_t i3 = 0; i3 < dim_3; i3 += 1) {
          for (std::size_t i4 = 0; i4 < dim_4; i4 += 1) {
            for (std::size_t p = 0; p < dim_1; p += 1) {
              tensor_c(i1, i2, i3, i4) +=
                  2 * factor * tensor_a_1(i1, p) * tensor_b(p, i2, i3, i4);
            }
            // for (std::size_t p = 0; p < dim_2; p += 1) {
            //   tensor_c(i1, i2, i3, i4) +=
            //       factor * tensor_a_2(i2, p) * tensor_b(i1, p, i3, i4);
            // }
            for (std::size_t p = 0; p < dim_3; p += 1) {
              tensor_c(i1, i2, i3, i4) -=
                  2 * factor * tensor_a_3(p, i3) * tensor_b(i1, i2, p, i4);
            }
            // for (std::size_t p = 0; p < dim_4; p += 1) {
            //   tensor_c(i1, i2, i3, i4) -=
            //       factor * tensor_a_4(p, i4) * tensor_b(i1, i2, i3, p);
            // }
          }
        }
      }
    }
  }

  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    const auto chankey_c = ms_2b.ChannelAtIndex(chan_c_index).ChannelKey();

    imsrg::AntisymmetrizeOperatorInChannel(c, chankey_c);
  }
}

void EvaluateScalar122CommutatorRefImplWithFactor(const Scalar1BOperator& a,
                                                  const Scalar2BOperator& b,
                                                  Scalar2BOperator& c,
                                                  int factor) {
  Expects(b.GetModelSpacePtr() == c.GetModelSpacePtr());
  Expects(c.Herm() == Hermiticity::CommutatorHermiticity(a.Herm(), b.Herm()));

  const auto& ms_1b = a.GetModelSpace();
  const auto& ms_2b = b.GetModelSpace();

  for (std::size_t chan_c_index = 0; chan_c_index < ms_2b.NumberOfChannels();
       chan_c_index += 1) {
    std::size_t chan_b_index = chan_c_index;

    const auto& chan_c = ms_2b.ChannelAtIndex(chan_c_index);
    const auto& chan_1 = chan_c.BraChannel1();
    const auto& chan_2 = chan_c.BraChannel2();
    const auto& chan_3 = chan_c.KetChannel1();
    const auto& chan_4 = chan_c.KetChannel2();

    imsrg::Scalar1BChannelKey chankey_a_1(chan_1.ChannelKey(),
                                          chan_1.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_2(chan_2.ChannelKey(),
                                          chan_2.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_3(chan_3.ChannelKey(),
                                          chan_3.ChannelKey());
    imsrg::Scalar1BChannelKey chankey_a_4(chan_4.ChannelKey(),
                                          chan_4.ChannelKey());

    // We assume these are all in ms_1b
    // If they are not, it is a runtime error that will be detected
    // (assuming debugging is not turned off)
    const auto chan_a_1_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_1);
    const auto chan_a_2_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_2);
    const auto chan_a_3_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_3);
    const auto chan_a_4_index = ms_1b.IndexOfChannelInModelSpace(chankey_a_4);

    auto& tensor_c = c.GetMutableTensorAtIndex(chan_c_index);
    const auto& tensor_b = b.GetTensorAtIndex(chan_b_index);
    const auto& tensor_a_1 = a.GetTensorAtIndex(chan_a_1_index);
    const auto& tensor_a_2 = a.GetTensorAtIndex(chan_a_2_index);
    const auto& tensor_a_3 = a.GetTensorAtIndex(chan_a_3_index);
    const auto& tensor_a_4 = a.GetTensorAtIndex(chan_a_4_index);

    // Dims
    const auto dim_1 = chan_1.size();
    const auto dim_2 = chan_2.size();
    const auto dim_3 = chan_3.size();
    const auto dim_4 = chan_4.size();

    for (std::size_t i1 = 0; i1 < dim_1; i1 += 1) {
      for (std::size_t i2 = 0; i2 < dim_2; i2 += 1) {
        for (std::size_t i3 = 0; i3 < dim_3; i3 += 1) {
          for (std::size_t i4 = 0; i4 < dim_4; i4 += 1) {
            for (std::size_t p = 0; p < dim_1; p += 1) {
              tensor_c(i1, i2, i3, i4) +=
                  factor * tensor_a_1(i1, p) * tensor_b(p, i2, i3, i4);
            }
            for (std::size_t p = 0; p < dim_2; p += 1) {
              tensor_c(i1, i2, i3, i4) +=
                  factor * tensor_a_2(i2, p) * tensor_b(i1, p, i3, i4);
            }
            for (std::size_t p = 0; p < dim_3; p += 1) {
              tensor_c(i1, i2, i3, i4) -=
                  factor * tensor_a_3(p, i3) * tensor_b(i1, i2, p, i4);
            }
            for (std::size_t p = 0; p < dim_4; p += 1) {
              tensor_c(i1, i2, i3, i4) -=
                  factor * tensor_a_4(p, i4) * tensor_b(i1, i2, i3, p);
            }
          }
        }
      }
    }
  }
}

}  // namespace detail
}  // namespace imsrg
