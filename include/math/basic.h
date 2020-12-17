//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_BASIC_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_BASIC_H_

#include "traits.h"

namespace cqf {

/**
 * nan
 *
 * @tparam Numeric
 * @param x
 * @return true only if x != x
 */
template<typename Numeric>
inline static constexpr
bool
nan(Numeric x) {
  return x != x;
}

/**
 * finite
 *
 * @tparam Numeric
 * @param x
 * @return true only if x is finite
 */
template<typename Numeric>
inline static constexpr
bool
finite(Numeric x) {
  return x != limits<Numeric>::infinity() && x != -limits<Numeric>::infinity();
}

/**
 * abs
 *
 * @tparam Numeric
 * @param x
 * @return absolute value of x
 */
template<typename Numeric>
inline static constexpr
Numeric
abs(Numeric x) noexcept {
  return
      (x == static_cast<Numeric>(0)) ? static_cast<Numeric>(0) : // deals with negative zero
      (x > static_cast<Numeric>(0)) ? x : -x;
}; // func abs

/**
 * floor
 *
 * @tparam Numeric
 * @param x
 * @return the greatest integer value in floating point format no greater than x
 */
template<typename Numeric>
inline static constexpr
Numeric
floor(Numeric x) noexcept {
  return nan(x) or x == limits<Numeric>::infinity() ? x :   //  nan / infinity
         static_cast<Numeric>(static_cast<long long>(x)) == x ? x :                    //  integer
         static_cast<Numeric>(static_cast<long long>(x) + (x > 0. ? 0 : -1));          //  floor
}

/**
 * ceil
 *
 * @tparam Numeric
 * @param x
 * @return the least integer value in floating point format no less than x
 */
template<typename Numeric>
inline static constexpr
Numeric
ceil(Numeric x) noexcept {
  return nan(x) or x == limits<Numeric>::infinity() ? x :   //  nan / infinity
         static_cast<Numeric>(static_cast<long long>(x)) == x ? x :                    //  integer
         static_cast<Numeric>(static_cast<long long>(x) + (x > 0. ? 1 : 0));           //  ceil
}

/**
 * parity check
 *
 * @tparam Integral
 * @param x
 * @return whether given integer is odd number
 */
template<typename Integral, typename =integral_guard<Integral>>
inline static constexpr
bool
odd(Integral x) noexcept {
  return x & static_cast<Integral>(1);
}

/**
 * parity check
 *
 * @tparam Integral
 * @param x
 * @return whether given integer is even number
 */
template<typename Integral, typename =integral_guard<Integral>>
inline static constexpr
bool
even(Integral x) noexcept {
  return !odd(x);
}

/**
 * min
 *
 * @tparam Numeric1
 * @tparam Numeric2
 * @param x
 * @param y
 * @return lesser of the two
 */
template<typename Numeric1, typename Numeric2>
inline static constexpr
common<Numeric1, Numeric2>
min(Numeric1 x, Numeric2 y) noexcept {
  return static_cast<common<Numeric1, Numeric2>>(x <= y ? x : y);
}

/**
 * min
 *
 * @tparam Numeric
 * @tparam Numerics
 * @param x
 * @param numerics
 * @return least of the group
 */
template<typename Numeric, typename... Numerics>
inline static constexpr
common<Numeric, Numerics...>
min(Numeric x, Numerics... numerics) noexcept {
  return static_cast<common < Numeric, Numerics...>>(x <= min(numerics...) ? x : min(numerics...));
}

/**
 * max
 *
 * @tparam Numeric1
 * @tparam Numeric2
 * @param x
 * @param y
 * @return greater of the two
 */
template<typename Numeric1, typename Numeric2>
inline static constexpr
common<Numeric1, Numeric2>
max(Numeric1 x, Numeric2 y) noexcept {
  return static_cast<common<Numeric1, Numeric2>>(x >= y ? x : y);
}

/**
 * max
 * @tparam Numeric
 * @tparam Numerics
 * @param x
 * @param numerics
 * @return greater of the group
 */
template<typename Numeric, typename... Numerics>
inline static constexpr
common<Numeric, Numerics...>
max(Numeric x, Numerics... numerics) noexcept {
  return static_cast<common < Numeric, Numerics...>>(x >= max(numerics...) ? x : max(numerics...));
}

/**
 * round
 * @tparam Numeric
 * @param x
 * @return the number rounded to the nearest whole number, or the greater of the two nearest
 */
template<typename Numeric>
inline static constexpr
Numeric
round(Numeric x) noexcept {
  return nan(x) or !finite(x) ? x :   //  nan / infinity
         static_cast<Numeric>(floor(x + 0.5));
}

/**
 * fraction
 *
 * @tparam Numeric
 * @param x
 * @return the fractional part of the floating point number
 */
template<typename Numeric>
inline static constexpr
Numeric
fraction(Numeric x) noexcept {
  return nan(x) or !finite(x) ? x :   //  nan / infinity
         static_cast<Numeric>(x - floor(x + 0.5));
}

/**
 * computes the sum of two variables
 *
 * @tparam Numeric1
 * @tparam Numeric2
 * @param x
 * @param y
 * @return
 */
template<typename Numeric1, typename Numeric2>
inline static constexpr
common<Numeric1, Numeric2>
sum(Numeric1 x, Numeric2 y) {
  return x + y;
}

/**
 * computes the sum of a list of variables
 *
 * @tparam Numeric
 * @tparam Numerics
 * @param x
 * @param numerics
 * @return
 */
template<typename Numeric, typename ... Numerics>
inline static constexpr
common<Numeric, Numerics...>
sum(Numeric x, Numerics... numerics) {
  return sum(x, sum(numerics...));
}

/**
 * computes the product of two variables
 *
 * @tparam Numeric1
 * @tparam Numeric2
 * @param x
 * @param y
 * @return
 */
template<typename Numeric1, typename Numeric2>
inline static constexpr
common<Numeric1, Numeric2>
prod(Numeric1 x, Numeric2 y) {
  return x * y;
}

/**
 * computes the product of a list of variables
 *
 * @tparam Numeric
 * @tparam Numerics
 * @param x
 * @param numerics
 * @return
 */
template<typename Numeric, typename ... Numerics>
inline static constexpr
common<Numeric, Numerics...>
prod(Numeric x, Numerics... numerics) {
  return prod(x, prod(numerics...));
}
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_BASIC_H_
