//
// Created by mamin on 12/16/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_NORM_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_NORM_H_

#include "traits.h"
#include "erf.h"
#include "sqrt.h"

namespace cqf {
template<typename Numeric>
inline static constexpr
promoted<Numeric>
norm_cdf(Numeric x) noexcept {
  return 0.5 * (1. + erf(x / constants<Numeric>::sqrt2));
}; // func norm_cdf
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_NORM_H_
