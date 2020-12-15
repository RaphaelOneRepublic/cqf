//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_GCD_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_GCD_H_

#include "traits.h"

namespace cqf {
/**
 * uses Euclid's algorithm to compute the greatest common divisor
 * @tparam Integral1
 * @tparam Integral2
 * @param x
 * @param y
 * @return
 */
template<typename Integral1, typename Integral2,
    typename = integral_guard<Integral1>, typename= integral_guard<Integral2>>
common<Integral1, Integral2>
gcd(Integral1 x, Integral2 y) {
  return y == 0 ? x : gcd(y, x % y);
}

/**
 * compute the least common multiple using the fact that lcm = x * y / gcd(x, y)
 *
 * @tparam Integral1
 * @tparam Integral2
 * @param x
 * @param y
 * @return
 */
template<typename Integral1, typename Integral2,
    typename = integral_guard<Integral1>, typename= integral_guard<Integral2>>
common<Integral1, Integral2>
lcm(Integral1 x, Integral2 y) {
  return x * y / gcd(x, y);
}
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_GCD_H_
