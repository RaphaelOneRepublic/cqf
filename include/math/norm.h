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
  return 0.5 * (1. + erf(x / constants < promoted < Numeric >> ::sqrt2));
} // func norm_cdf

template<typename Numeric>
inline static constexpr
promoted<Numeric>
norm_pdf(Numeric x) noexcept {
  return 1. / sqrt(2. * constants < promoted < Numeric >> ::pi) * exp(-0.5 * x * x);
} // func norm_pdf
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MATH_NORM_H_
