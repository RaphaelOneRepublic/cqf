//
// Created by mamin on 12/17/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_

#include "math/traits.h"

namespace cqf {
/**
 * represents a coupon paying bond
 * @tparam Float
 * @tparam Int
 */
template<typename Float, typename Int, typename =floating_guard<Float>, typename = integral_guard<Int>>
class coupon_bond {
 protected:
  /**
   * time to maturity in years
   */
  Float T;

  /**
   * coupon rate in percentage,
   * 4 for 4% coupon rate
   */

  Float r;
  /**
   * coupon payments per annum.
   * 1 for annual;
   * 2 for semiannual (bond equivalent);
   * 4 for quarterly;
   * 12 for monthly (mortgage equivalent).
   */
  Int m;

 public:
  inline explicit constexpr
  coupon_bond(Float T, Float r, /*default is a semiannual coupon bond*/ Int m = 2)
      : T(T), r(r), m(m) {}

};

} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_
