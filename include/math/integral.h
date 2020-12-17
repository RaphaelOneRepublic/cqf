//
// Created by mamin on 12/17/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_INTEGRAL_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_INTEGRAL_H_

#include "traits.h"

namespace cqf {

namespace impl {
/**
 * incrementally adds function terms.
 *
 * @tparam Float
 * @param func function-like
 * @param acc result accumulator
 * @param cur current term
 * @param step increment in independent variable
 * @param end stopping endpoint
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
integrate_sum(const univariate_real_func<Float> &func, Float acc, Float cur, Float step, Float end) {
  return cur > end ? acc :
         integrate_sum(func, acc + func(cur), cur + step, step, end);
}

/**
 * uses a specified partition size to compute the Riemann sum of a function.
 *
 * @tparam Float
 * @param func function-like
 * @param a left endpoint
 * @param b right endpoint
 * @param step size of partitions
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
integrate_impl(const univariate_real_func<Float> &func, Float a, Float b, Float step) {
  return
      step / 3. *
          (
              sum(func(a), func(b), // terminal
                  integrate_sum(func, static_cast<Float>(0), a + step, step * 2, b) * 4., // midpoints
                  integrate_sum(func, static_cast<Float>(0), a + 2 * step, 2 * step, b - step) * 2. // endpoints
              )
          );
}

/**
 * uses a specified partition number to compute the Riemann sum of a function.
 *
 * @tparam Float
 * @param func
 * @param a
 * @param b
 * @param n
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
integrate_part(const univariate_real_func<Float> &func, Float a, Float b, size_t n) {
  return impl::integrate_impl(func, a, b, (b - a) / n);
}

/**
 * recursively approximates the function integral by using finer and finer partitions.
 *
 * @tparam Float
 * @param func
 * @param a
 * @param b
 * @param cur
 * @param prev
 * @param n
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float
integrate_recur(const univariate_real_func<Float> &func, Float a, Float b, Float cur, Float prev, size_t n) {
<<<<<<< HEAD
  return (
             /*acceptable error rate*/ abs(cur - prev) < limits<Float>::epsilon() * abs(cur) &&
          /*at least 16 partitions
           *2 iterations to get rid of the initial two guesses*/  n > CQF_MINIMUM_SIMPSON_PARTITION
         ) /*maximum partitions*/ || (n > CQF_MAXIMUM_SIMPSON_PARTITION) ? cur :
         /*double partition numbers*/ integrate_recur(func, a, b, integrate_part(func, a, b, n * 2), cur, n * 2);
=======
  return (abs(cur - prev) < limits<Float>::epsilon() * abs(cur) && n > 16) || (n > 65536) ? cur :
         integrate_recur(func, a, b, integrate_part(func, a, b, n * 2), cur, n * 2);
>>>>>>> origin/master
}

} // namespace impl

/**
 * integrate a real-valued function over an interval
 *
 * @tparam Float
 * @param func function-like
 * @param a left endpoint
 * @param b right endpoint
 * @return
 */
template<typename Float, typename =floating_guard<Float>>
inline static constexpr
Float integrate(const univariate_real_func<Float> &func, Float a, Float b) {
<<<<<<< HEAD
  return impl::integrate_recur(func, a, b, 1., 0., /*initial 4 partitions*/4);
=======
  return impl::integrate_recur(func, a, b, 1., 0., 4);
>>>>>>> origin/master
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_INTEGRAL_H_
