//
// Created by mamin on 12/15/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_CONSTANTS_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_CONSTANTS_H_

#include "traits.h"

namespace cqf {
template<typename Numeric, typename = floating_guard<Numeric>>
struct constants {
  inline static constexpr Numeric pi
      = static_cast<Numeric>(3.1415926535897932384626433832795028841972l);

  inline static constexpr Numeric e
      = static_cast<Numeric>(2.7182818284590452353602874713526624977572l);

  inline static constexpr Numeric _2pi = 2. * pi;

  inline static constexpr Numeric _half_pi = 0.5 * pi;
};
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_CONSTANTS_H_
