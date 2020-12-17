//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_

#include <cmath>
#include <functional>
#include <limits>
#include <type_traits>

/**
 * Due to the fact that some compiler might treat standard math functions as constexpr functions,
 * the implementations may directly call these for maximized performance.
 * On to get rid of standard library implementations
 */
#define CQF_FORCE_NO_STL 1

#ifndef _GLIBCXX_CONSTEXPR
#define _GLIBCXX_CONSTEXPR
#endif
/**
 * whether to fallback to constexpr std
 */
#define CQF_CONSTEXPR_STL_FALLBACK (_GLIBCXX_CONSTEXPR == constexpr && !CQF_FORCE_NO_STL)

/**
 * initial guess used in newton's method in search for the real implied volatility.
 * might somewhat affect convergence.
 */
#define CQF_DEFAULT_IMPLIED 0.5

/**
 * initial guess used in newton's method in search for the real implied yield to maturity.
 * might somewhat affect convergence.
 */
#define CQF_DEFAULT_YIELD 0.1

/**
 * multiple of a hundred.
 * default par value is $100.
 * CAUTION: values other than 1 are prone to static call stack errors
 */
#define CQF_DEFAULT_PAR_VALUE 1.

/**
 * how much the machine epsilon is to be scaled to be the absolute error between computed value and real value
 */
#define CQF_IMPLIED_ERROR_SCALE 1e2

/**
 * maximum / minimum recurrences
 */
#define CQF_MAX_TRIG_RECUR 16
#define CQF_MAX_EXP_RECUR 32
#define CQF_MAX_LOG_RECUR 512
#define CQF_MAXIMUM_SIMPSON_PARTITION 65536
#define CQF_MINIMUM_SIMPSON_PARTITION 16

namespace cqf {

template<typename... Numerics>
using floating_guard = std::conjunction<std::is_floating_point<Numerics>...>;

template<typename ... Numeric>
using integral_guard = std::conjunction<std::is_integral<Numeric>...>;

//template<typename Numeric>
//using floating_guard = std::enable_if<std::is_floating_point_v<Numeric>>;
//
//template<typename Numeric>
//using integral_guard = std::enable_if_t<std::is_integral_v<Numeric>>;

template<typename... Numerics>
using common = typename std::common_type_t<Numerics...>;

template<typename Numeric>
using promoted = std::conditional_t<std::is_floating_point_v<Numeric>, Numeric, double>;

template<typename... Numerics>
using common_promoted = promoted<common<Numerics...>>;

template<typename Numeric>
using limits = std::numeric_limits<Numeric>;

template<typename Dependent, typename... Ind>
using function = std::function<Dependent(Ind...)>;

template<typename Float, typename =floating_guard<Float>>
using univariate_real_func = function<Float, Float>;
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_TRAITS_H_
