//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SQRT_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SQRT_H_

#include <cstddef>

#include "traits.h"
#include "basic.h"

namespace cqf {
namespace impl {
template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float sqrt_recur(Float x, Float s0, Float s1, size_t recur) noexcept {
  return abs(s0 - s1) / s0 < limits<Float>::epsilon() or recur > 1024 ? s0 :
         sqrt_recur(x, static_cast<Float>(0.5) * (s0 + x / s0), s0, recur + 1);
}

template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float sqrt_impl(Float x) noexcept {
  return nan(x) or x == limits<Float>::infinity() ? x :
         x < 0 ? limits<Float>::quiet_NaN() :
         x == static_cast<Float>(0) ? static_cast<Float>(+0) :
         impl::sqrt_recur(x, static_cast<Float>(1), static_cast<Float>(0), 1);
}
} // namespace impl
template<typename Numeric>
inline static constexpr
promoted<Numeric>
sqrt(Numeric x) noexcept {
  return impl::sqrt_impl(static_cast<promoted<Numeric>>(x));
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SQRT_H_
