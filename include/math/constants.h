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
      = static_cast<Numeric>(3.14159265358979323846264338327950288419716939937510l);

  inline static constexpr Numeric e
      = static_cast<Numeric>(2.71828182845904523536028747135266249775724709369995l);

  inline static constexpr Numeric sqrt2
      = static_cast<Numeric>(1.41421356237309504880168872420969807856967187537694l);

  inline static constexpr Numeric _2pi = 2. * pi;

  inline static constexpr Numeric _half_pi = 0.5 * pi;
};
} // namespace cqf
#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_CONSTANTS_H_
