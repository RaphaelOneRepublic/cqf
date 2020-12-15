//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_POWER_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_POWER_H_

#include "traits.h"
#include "basic.h"

namespace cqf {
namespace impl {
template<typename Numeric, typename Integral, typename = integral_guard<Integral>>
inline static constexpr
Numeric
power_impl(Numeric x, Numeric acc, Integral n) {
  return n < 0. ? power_impl(static_cast<Numeric>(1.) / x, acc, -n) :
         n == 0. ? acc :
         n == 1. ? acc * x :
         even(n) ? power_impl(x * x, acc, n / 2) :
         power_impl(x * x, x * acc, (n - 1) / 2);
}
} // namespace impl
/**
 * compute an integral power of a floating point number using Squaring the Exponential algorithm
 * @tparam Numeric
 * @tparam Integral
 * @param x
 * @param n
 * @return x raised to the power of n
 */
template<typename Numeric, typename Integral, typename = integral_guard<Integral>>
inline static constexpr
Numeric
power(Numeric x, Integral n) {
  return impl::power_impl(x, static_cast<Numeric>(1), n);
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_POWER_H_
