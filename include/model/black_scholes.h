//
// Created by mamin on 12/16/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_

#include "math/traits.h"
#include "math/norm.h"
#include "math//log.h"

namespace cqf {
template<typename F, typename = floating_guard<F>>
class vanilla {
  F S_;
  F K_;
  F r_;
  F q_;
  F T_;
  F sigma_;
  F premium_;

  F d1_;
  F d2_;

 public:
  inline explicit constexpr
  vanilla(F S, F K, F T, F r, F sigma, F q = 0) {
    S_ = S;
    K_ = K;
    r_ = r;
    q_ = q;
    T_ = T;
    sigma_ = sigma;

    compute();
  }

  inline constexpr
  void compute() {
    d1_ = (ln(S_ / K_) + (r_ + 0.5 * sigma_ * sigma_) * T_) / (sigma_ * sqrt(T_));
    d2_ = d1_ - sigma_ * sqrt(T_);
    premium_ = S_ * exp(-q_ * T_) * norm_cdf(d1_) - K_ * exp(-r_ * T_) * norm_cdf(d2_);
  }

  inline constexpr
  F premium() noexcept {
    return premium_;
  }
};
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_
