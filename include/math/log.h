//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_LOG_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_LOG_H_

#include <cstddef>

#include "traits.h"
#include "basic.h"
#include "constants.h"
#include "exp.h"

namespace cqf {
namespace impl {
/**
 * iteratively compute natural logarithm using Newton-Raphson's method
 *
 * @tparam Float
 * @param x
 * @param l0
 * @param l1
 * @param recur
 * @return
 */
template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float
ln_recur(Float x, Float l0, Float l1, size_t recur) noexcept {
  return abs(l0 - l1) / l0 < limits<Float>::epsilon() or recur > 512 ? l0 :
         ln_recur(x, l0 + static_cast<Float>(2.) * (x - exp(l0)) / (x + exp(l0)), l0, recur + 1);
}

template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float
ln_reduce(Float x) noexcept {
  return limits<Float>::epsilon() > abs(x - constants<Float>::e) ? static_cast<Float>(1) :
         x > constants<Float>::e ? ln_reduce(x / constants<Float>::e) + static_cast<Float>(1) :
         ln_recur(x, x, static_cast<Float>(0.), 1);
}

template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float
ln_impl(Float x) noexcept {
  return nan(x) or x == limits<Float>::infinity() ? x :
         x <= static_cast<Float>(0.) ? limits<Float>::quiet_NaN() :
         x == static_cast<Float>(1.) ? static_cast<Float>(0) :
         x < static_cast<Float>(1.) ? -ln_reduce(static_cast<Float>(1.) / x) :
         ln_reduce(x);

}
} // namespace impl
/**
 * Natural logarithm, i.e. logarithm with Euler number as base
 * <br/>
 * A compromise has been made here for preciser answer for x's near 1,
 * but the method cannot compute extremely large or small answers due to its use of the exponential
 *
 * @tparam Numeric
 * @param x
 * @return log(x)
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
ln(Numeric x) noexcept {
  return x == static_cast<Numeric>(2) ? static_cast<promoted<Numeric>>(0.6931471805599453094172321214581765680755l) :
         x == static_cast<Numeric>(10) ? static_cast<promoted<Numeric>>(2.3025850929940456840179914546843642076011l) :
         impl::ln_impl(static_cast<promoted<Numeric>>(x));
}

/**
 * Base 2 logarithm
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
log2(Numeric x) noexcept {
  return ln(x) / ln(static_cast<Numeric>(2));
}

/**
 * Base 10 logarithm
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
log10(Numeric x) noexcept {
  return ln(x) / ln(static_cast<Numeric>(10));
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_LOG_H_
