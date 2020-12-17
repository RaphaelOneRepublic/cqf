//
// Created by mamin on 12/17/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_

#include "math/traits.h"

namespace cqf {
/**
 * represents a coupon paying bond.
 * @tparam Float
 * @tparam Int
 */
template<typename Float, typename Int=int8_t, typename =floating_guard<Float>, typename = integral_guard<Int>>
class coupon_bond {
 private:
  /**
   * time to maturity in years.
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

  /**
   * implied yield to maturity.
   */
  Float yield;

 public:
  /**
   * constructor.
   *
   * @param T
   * @param r
   * @param yield
   * @param m
   */
  inline explicit constexpr
  coupon_bond(Float T, Float r, Float yield,/*default is a semiannual coupon bond*/ Int m = 2)
      : T(T), r(r), m(m), yield(yield) {}

  /**
   * yield to maturity.
   *
   * @return
   */
  inline constexpr Float yield_to_maturity() const { return yield; };

  /**
   * fair price of bond's cash flows discounted at yield to maturity.
   *
   * @return
   */
  inline constexpr
  Float
  price() const {
    return present_value_until_impl(0., T - 1. / static_cast<Float>(m)) // up to the last but one coupon payment
        + CQF_DEFAULT_PAR_VALUE * (100. + r / m) * exp(-yield * T); // last coupon payment and principal
  }

  /**
   * duration of bond.
   * modified duration = (-1 / B) * (dB / dY).
   *
   * @return
   */
  inline constexpr
  Float
  duration() const {
    return -dBdY() / price();
  }

  /**
   * convexity of bond.
   * convexity = (1 / B) * (d^2B / dY^2)
   *
   * @return
   */
  inline constexpr
  Float
  convexity() const {
    return d2BdY2() / price();
  }

 private:
  /**
   * present value of cash flows up until time t discounted at yield to maturity added with a value.
   *
   * @param acc
   * @param t
   * @return
   */
  inline constexpr
  Float
  present_value_until_impl(Float acc, Float t) const {
    return t < limits<Float>::epsilon() * T ? acc :
           present_value_until_impl(acc + CQF_DEFAULT_PAR_VALUE * (r / m) * exp(-yield * t),
                                    t - 1. / static_cast<Float>(m));
  }

  /**
   * first derivative of present value with respect to yield to maturity.
   *
   * @return
   */
  inline constexpr
  Float
  dBdY() const {
    return dBdY_until_impl(0., T - 1. / static_cast<Float>(m)) // up to the last but one coupon payment
        - T * CQF_DEFAULT_PAR_VALUE * (100. + r / m) * exp(-yield * T); // last coupon payment and principal
  }

  /**
   * first derivative of present with respect yo yield to maturity computed.
   *
   * @param acc
   * @param t
   * @return
   */
  inline constexpr
  Float
  dBdY_until_impl(Float acc, Float t) const {
    return t < limits<Float>::epsilon() * T ? acc :
           dBdY_until_impl(acc - t * CQF_DEFAULT_PAR_VALUE * (r / m) * exp(-yield * t),
                           t - 1. / static_cast<Float>(m));
  }

  /**
 * second derivative of present value with respect to yield to maturity.
 *
 * @return
 */
  inline constexpr
  Float
  d2BdY2() const {
    return d2BdY2_until_impl(0., T - 1. / static_cast<Float>(m)) // up to the last but one coupon payment
        + T * T * CQF_DEFAULT_PAR_VALUE * (100. + r / m) * exp(-yield * T); // last coupon payment and principal
  }

  /**
   * second derivative of present with respect yo yield to maturity computed.
   *
   * @param acc
   * @param t
   * @return
   */
  inline constexpr
  Float
  d2BdY2_until_impl(Float acc, Float t) const {
    return t < limits<Float>::epsilon() * T ? acc :
           d2BdY2_until_impl(acc + t * t * CQF_DEFAULT_PAR_VALUE * (r / m) * exp(-yield * t),
                             t - 1. / static_cast<Float>(m));
  }

 public:
  /**
   * obtain a bond with the provided information, with yield to maturity unknown and computed from the traded price.
   *
   * @param T
   * @param r
   * @param price
   * @param m
   * @return
   */
  inline static constexpr
  coupon_bond<Float, Int>
  with_price(Float T, Float r, Float price, Int m = 2) {
    return with_price_newt(coupon_bond(T, r, CQF_DEFAULT_YIELD, m), price);
  }

 private:
  /**
   * compute the implied yield to maturity from traded price using Newton's method.
   *
   * @param cb
   * @param price
   * @return
   */
  inline static constexpr
  coupon_bond<Float, Int>
  with_price_newt(coupon_bond<Float, Int> cb, Float price) {
    return CQF_IMPLIED_ERROR_SCALE
               * limits<Float>::epsilon() > abs(cb.price() - price) ? cb :
           with_price_newt(
               coupon_bond(cb.T, cb.r,
                           cb.yield - (cb.price() - price) / cb.dBdY(),
                           cb.m),
               price
           );
  }
};
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_COUPON_BOND_H_
