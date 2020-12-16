//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_

#include <type_traits>
#include <limits>
#include <cmath>

/**
 * Due to the fact that some compiler might treat standard math functions as constexpr functions,
 * the implementations may directly call these for maximized performance.
 * On to get rid of standard library implementations
 */
#define FORCE_SHADOW_STD 1

#ifndef _GLIBCXX_CONSTEXPR
#define _GLIBCXX_CONSTEXPR
#endif

#define USE_CONSTEXPR_STD (_GLIBCXX_CONSTEXPR == constexpr && !FORCE_SHADOW_STD)

namespace cqf {
template<typename Numeric>
using floating_guard = std::enable_if_t<std::is_floating_point_v<Numeric>>;

template<typename Numeric>
using integral_guard = std::enable_if_t<std::is_integral_v<Numeric>>;

template<typename... Numerics>
using common = typename std::common_type_t<Numerics...>;

template<typename Numeric>
using promoted = std::conditional_t<std::is_floating_point_v<Numeric>, Numeric, double>;

template<typename... Numerics>
using common_promoted = promoted<common<Numerics...>>;

template<typename Numeric>
using limits = std::numeric_limits<Numeric>;
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_
