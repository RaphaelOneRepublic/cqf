//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SIN_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SIN_H_

#include <cstddef>

#include "traits.h"
#include "basic.h"

namespace cqf {
namespace impl {
/**
 * recursively computes the taylor expansion of sin(x)
 *
 * @tparam Float
 * @param x
 * @param acc
 * @param fac
 * @param recur
 * @return
 */
template<typename Float, typename = floating_guard<Float>>
Float
sin_recur(Float x, Float acc, Float fac, size_t recur) {
  return recur > 16 ? acc :
         sin_recur(x, acc + fac,
                   -fac * x * x / (static_cast<Float>(2.) * static_cast<Float>(recur))
                       / (static_cast<Float>(2.) * static_cast<Float>(recur) + 1),
                   recur + 1);
}

/**
 * wrapper for sin_recur() with initial accumulator cleared, first term set to x and recur set to 1
 *
 * @tparam Float
 * @param x
 * @return
 */
template<typename Float, typename = floating_guard<Float>>
Float
sin_reduce(Float x) {
  return impl::sin_recur(x, static_cast<Float>(0), x, 1);
}

/**
 * type check, range check
 * shift input so that x is in the range [0, 2*pi]
 *
 * @tparam Float
 * @param x
 * @return
 */
template<typename Float, typename = floating_guard<Float>>
Float
sin_impl(Float x) {
  return nan(x) or x == limits<Float>::infinity() or x == -limits<Float>::infinity() ? limits<Float>::quiet_NaN() :
         -2 * constants<Float>::pi <= x and x <= 2 * constants<Float>::pi ? sqrt_impl(x) :
         sin_reduce(fraction(x / constants<Float>::pi / 2) * 2 * constants<Float>::pi);
}
} // namespace impl

/**
 * sine
 * computes the sine function using Taylor expansion
 *
 * @tparam Numeric
 * @param x
 * @return sin(x)
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
sin(Numeric x) {
  return impl::sin_impl(static_cast<promoted<Numeric>>(x));
}
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_SIN_H_
