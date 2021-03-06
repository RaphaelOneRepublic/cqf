//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRIG_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRIG_H_

#include <cstddef>

#include "traits.h"
#include "basic.h"
#include "constants.h"

namespace cqf {
namespace impl {
template<typename Float, typename = floating_guard<Float>>
inline static constexpr
Float wrap_angle_impl(Float x) noexcept {
  return nan(x) or x == limits<Float>::infinity() or x == -limits<Float>::infinity() ? limits<Float>::quiet_NaN() :
         x >= -constants<Float>::pi and x < constants<Float>::pi ? x :
         fraction(x / constants<Float>::_2pi) * constants<Float>::_2pi;
}
} // namespace impl

/**
 * normalize the angle to fit in the range [-pi, +pi)
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
wrap_angle(Numeric x) noexcept {
  return impl::wrap_angle_impl(static_cast<promoted<Numeric>>(x));
}

/**
 * convert from degree to radian
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
rad(Numeric x) noexcept {
  return static_cast<promoted<Numeric>>(x) / 180. * constants < promoted < Numeric >> ::pi;
}

/**
 * convert from radian to degree
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
deg(Numeric x) noexcept {
  return static_cast<promoted<Numeric>>(x) * 180. / constants < promoted < Numeric >> ::pi;
}

namespace impl {
/**
 * iteratively expands sine function with Taylor series
 *
 * @tparam Float
 * @param x
 * @param acc
 * @param fac
 * @param recur
 * @return
 */
template<typename Float, typename  = floating_guard<Float>>
inline static constexpr
promoted<Float>
sin_recur(Float x, Float acc, Float fac, size_t recur) noexcept {
  return recur > CQF_MAX_TRIG_RECUR ? acc :
         sin_recur(x, acc + fac,
                   -fac * x * x / (2. * static_cast<Float>(recur)) / (2. * static_cast<Float>(recur) + 1.), recur + 1);
}
/**
 * sine of normalized angle
 *
 * @tparam Float
 * @param x
 * @return
 */
template<typename Float, typename  = floating_guard<Float>>
inline static constexpr
promoted<Float>
sin_impl(Float x) noexcept {
  return limits<Float>::epsilon() > abs(x + constants<Float>::pi) ? 0 :
         sin_recur(x, static_cast<Float>(0), x, 1);
}
} // namespace impl

/**
 * sine function
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
sin(Numeric x) noexcept {
  return impl::sin_impl(wrap_angle(x));
}

namespace impl {
/**
 * iteratively expands cosine function with Taylor series
 *
 * @tparam Float
 * @param x
 * @param acc
 * @param fac
 * @param recur
 * @return
 */
template<typename Float, typename  = floating_guard<Float>>
inline static constexpr
promoted<Float>
cos_recur(Float x, Float acc, Float fac, size_t recur) noexcept {
  return recur > CQF_MAX_TRIG_RECUR ? acc :
         cos_recur(x, acc + fac,
                   -fac * x * x / (2. * static_cast<Float>(recur)) / (2. * static_cast<Float>(recur) - 1.), recur + 1);
}

/**
 * cosine of normalized angle
 *
 * @tparam Float
 * @param x
 * @return
 */
template<typename Float, typename  = floating_guard<Float>>
inline static constexpr
promoted<Float>
cos_impl(Float x) noexcept {
  return limits<Float>::epsilon() > abs(x + constants<Float>::pi) ? -1 :
         limits<Float>::epsilon() > abs(x) ? 1 :
         limits<Float>::epsilon() > abs(x + constants<Float>::_half_pi) ? 0 :
         limits<Float>::epsilon() > abs(x - constants<Float>::_half_pi) ? 0 :
         cos_recur(x, static_cast<Float>(0), static_cast<Float>(1), 1);
}
} // namespace impl

/**
 * cosine function
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
cos(Numeric x) noexcept {
  return impl::cos_impl(wrap_angle(x));
}

/**
 * tangent function
 * TODO use taylor approximation expansion can save computation
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
inline static constexpr
promoted<Numeric>
tan(Numeric x) noexcept {
  return sin(x) / cos(x);
}

/**
 * secant function
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
promoted<Numeric>
sec(Numeric x) noexcept {
  return 1. / cos(x);
}

/**
 * cosecant function
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
promoted<Numeric>
csc(Numeric x) noexcept {
  return 1. / sin(x);
}

/**
 * cotangent function
 * this computation is rather slow
 *
 * @tparam Numeric
 * @param x
 * @return
 */
template<typename Numeric>
promoted<Numeric>
ctg(Numeric x) noexcept {
  return cos(x) / sin(x);
}
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRIG_H_
