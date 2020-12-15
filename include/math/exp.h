//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_EXP_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_EXP_H_

#include "traits.h"
#include "basic.h"
#include "power.h"
#include "constants.h"

namespace cqf {
namespace impl {
/**
 * use Taylor expansion to approximate exp(x)
 * @tparam Float
 * @param x
 * @param recur
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
exp_taylor(Float x, size_t recur) noexcept {
  return recur > 32
         ? 1.
         : exp_taylor(x, recur + 1) * (x / static_cast<Float>(recur)) + 1.;
}

/**
 * computes the exp(x) where -0.5 <= x < 0.5
 * @tparam Float
 * @param x
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
exp_frac(Float x) noexcept {
  return x == 0. ? static_cast<Float>(1.) :
         x > 0. ? exp_taylor(x, 1) :
         1. / exp_taylor(abs(x), 1);
}

template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
exp_impl(Float x) noexcept {
  return x == -limits<Float>::infinity() ? 0. :
         x == limits<Float>::infinity() or nan(x) ? x :
         x == static_cast<Float>(0) ? 1. :
         power(constants<Float>::e, static_cast<long>(round(x))) * exp_frac(fraction(x));
}
} // namespace impl

/**
 * exponential function
 * @tparam Numeric
 * @param x
 * @return computes the euler number raised to the power of x
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
exp(Numeric x) noexcept {
  return impl::exp_impl(static_cast<promoted<Numeric>>(x));
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_EXP_H_
