//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_ERF_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_ERF_H_

#include <cstddef>

#include "traits.h"
#include "basic.h"

namespace cqf {
namespace impl {
/**
 * For small enough inputs, use Maclaurin series to approximate the value.
 * Though it converges for all x, the performance is famously poor for large inputs.
 *
 * @tparam Float
 * @param x
 * @param acc
 * @param fac
 * @param recur
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
erf_recur(Float x, Float acc, Float fac, size_t recur) noexcept {
  return abs(fac / acc) < limits<Float>::epsilon() or recur > 64 ? acc :
         erf_recur(x, acc + fac,
                   -fac * x * x
                       * (2. * static_cast<Float>(recur) - 1.)
                       / static_cast<Float>(recur)
                       / (2. * static_cast<Float>(recur) + 1.),
                   recur + 1);
}

/**
 * For large inputs, use the first few terms of the asymptotic expansion.
 * The expansion diverges quickly, and need be taken good care of.
 *
 * @tparam Float
 * @param x
 * @param acc
 * @param fac
 * @param recur
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
erf_recur_large(Float x, Float acc, Float fac, size_t recur) noexcept {
  return abs(fac / acc) < limits<Float>::epsilon() or recur > 9 ? acc :
         erf_recur_large(x, acc + fac, -fac * (2. * static_cast<Float>(recur) - 1.) / (2. * x * x), recur + 1);
}

template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
erf_impl(Float x) noexcept {
  return nan(x) ? x :
         x == limits<Float>::infinity() ? static_cast<Float>(1) :
         x == -limits<Float>::infinity() ? static_cast<Float>(-1) :
         x == static_cast<Float>(0) ? static_cast<Float>(0) :
         abs(x) <= 4 ? 2. * erf_recur(x, static_cast<Float>(0), x, 1) / sqrt(constants<Float>::pi) :
         1 - exp(-x * x)
             * erf_recur_large(x, static_cast<Float>(0), static_cast<Float>(1) / x, 1)
             / sqrt(constants<Float>::pi);
}
} // namespace impl
/**
 * error function
 * uses Maclaurin series to approximate the erf function
 *
 * @tparam Numeric
 * @param x
 * @return erf(x)
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
erf(Numeric x) noexcept {
  return impl::erf_impl(static_cast<promoted<Numeric>>(x));
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_ERF_H_
