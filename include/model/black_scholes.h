//
// Created by mamin on 12/16/2020.
//
#ifndef CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_
#define CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_

#include "math/traits.h"
#include "math/erf.h"
#include "math/log.h"
#include "math/sqrt.h"

namespace cqf {
/**
 * base class for European style plain vanilla options.
 *
 * @tparam Float
 */
template<typename Float, typename = floating_guard<Float>>
class vanilla_template {
 protected:
  Float S;        // spot underlying
  Float K;        // strike
  Float T;        // time to maturity
  Float r;        // risk-free interest rate
  Float q;        // dividend rate
  Float sigma;    // implied volatility


 public:
  /**
   * constructor.
   *
   * @param S underlying spot price
   * @param K strike price
   * @param T time to maturity
   * @param r risk-free interest rate
   * @param q dividend paying rate of underlying
   * @param sigma implied volatility
   */
  inline explicit constexpr
  vanilla_template(Float S, Float K, Float T, Float r, Float q, Float sigma)
      : S(S), K(K), T(T), r(r), q(q), sigma(sigma) {}

  /**
   * black scholes d1.
   * un-discounted delta.
   *
   * @return
   */
  inline constexpr
  Float d1() const {
    return (ln(S / K) + (r - q + 0.5 * sigma * sigma) * T) / sigma * sqrt(T);
  }

  /**
   * black scholes d2.
   * risk-neutral probability of expiring in the money.
   *
   * @return
   */
  inline constexpr
  Float d2() const {
    return (ln(S / K) + (r - q - 0.5 * sigma * sigma) * T) / sigma * sqrt(T);
  }

  /**
   * discounted value of underlying spot.
   *
   * @return
   */
  inline constexpr
  Float SPV() const {
    return S * exp(-q * T);
  }

  /**
   * discounted value of underlying strike.
   *
   * @return
   */
  inline constexpr
  Float KPV() const {
    return K * exp(-r * T);
  }

  inline constexpr
  Float implied_volatility() const { return sigma; };

  /**
   * value of option.
   *
   * @return
   */
  inline virtual Float premium() const { return 0; };

  /**
   * delta of option.
   * sensitivity of option value with respect to underlying price.
   * Delta = dV / dS.
   *
   * Virtual implementation. real implementations depend on whether the option is call or put.
   *
   * @return
   */
  inline virtual Float delta() const { return 0; };

  /**
   * theta of option.
   * sensitivity of option value with respect to time to maturity
   * Theta = dV / d tau.
   *
   * Virtual implementation. real implementations depend on whether the option is call or put.
   *
   * @return
   */
  inline virtual Float theta() const { return 0; }

  /**
   * rho of option.
   * sensitivity of option value with respect to risk-free interest rate.
   * Rho = dV / dr.
   *
   * Virtual implementation. real implementations depend on whether the option is call or put.
   *
   * @return
   */
  inline virtual Float rho() const { return 0; }

  /**
   * gamma of option.
   * sensitivity of option delta with respect to underlying price.
   * Gamma = d^2V / dS^2.
   *
   * Same for both call and put.
   *
   * @return
   */
  inline constexpr Float gamma() const {
    return exp(-q * T) * norm_pdf(d1()) / S / sigma / sqrt(T);
  };

  /**
   * vega of option.
   * sensitivity of option value with respect to implied volatility.
   * Vega = dV / d sigma.
   *
   * Same for both call and put.
   *
   * @return
   */
  inline constexpr Float vega() const {
    return SPV() * norm_pdf(d1()) * sqrt(T);
  }
};

/**
 * plain vanilla call options.
 *
 * @tparam Float
 */
template<typename Float, typename = floating_guard<Float>>
class call_vanilla : public vanilla_template<Float> {
 public:
  /**
   * constructor.
   *
   * @param S
   * @param K
   * @param T
   * @param r
   * @param q
   * @param sigma
   */
  inline explicit constexpr
  call_vanilla(Float S, Float K, Float T, Float r, Float q, Float sigma)
      : vanilla_template<Float>(S, K, T, r, q, sigma) {}

  /**
   * value of option.
   *
   * @return
   */
  inline constexpr
  Float premium() const {
    return this->SPV() * norm_cdf(this->d1()) - this->KPV() * norm_cdf(this->d2());
  }

  /**
   * delta of option.
   * sensitivity of option value with respect to underlying price.
   * Delta = dV / dS
   *
   * @return
   */
  inline constexpr
  Float delta() const {
    return exp(-this->q * this->T) * norm_cdf(this->d1());
  }

  /**
   * theta of option.
   * sensitivity of option value with respect to time to maturity
   * Theta = dV / d tau
   *
   * @return
   */
  inline constexpr
  Float theta() const {
    return -exp(-this->q * this->T) * this->S * norm_pdf(this->d1()) * this->sigma / 2. / sqrt(this->T)
        - this->r * this->KPV() * norm_cdf(this->d2())
        + this->q * this->SPV() * norm_cdf(this->d1());
  }

  /**
   * rho of option.
   * sensitivity of option value with respect to risk-free interest rate
   * Rho = dV / dr
   *
   * @return
   */
  inline constexpr
  Float rho() const {
    return this->T * this->KPV() * norm_cdf(this->d2());
  }

  /**
   * compute the implied volatility from the provided information,
   * and returns a plain vanilla call option instance with the computed implied volatility.
   *
   * @param S
   * @param K
   * @param T
   * @param r
   * @param q
   * @param price
   * @return
   */
  inline static constexpr
  call_vanilla<Float>
  implied(Float S, Float K, Float T, Float r, Float q, Float price) {
    return implied_newt(call_vanilla<Float>(S, K, T, r, q, CQF_DEFAULT_IMPLIED), price);
  }

 private:
  /**
   * uses newton's method to compute implied volatility.
   *
   * @param op
   * @param price
   * @return
   */
  inline static constexpr
  call_vanilla<Float>
  implied_newt(call_vanilla<Float> op, Float price) {
    return CQF_IMPLIED_ERROR_SCALE /*scaling factor to machine epsilon to compare with absolute error, this is sad*/
               * limits<Float>::epsilon() * price > abs(op.premium() - price)
           /*if error is acceptable*/ ? op :
           /*else*/ implied_newt(
            /*new option */ call_vanilla<Float>(op.S, op.K, op.T, op.r, op.q,
                /*new sigma by newton's*/ op.sigma - (/*func value*/op.premium() - price) / /*derivative*/ op.vega()),
            /*price unchanged*/ price);
  }
};

/**
 * plain vanilla put options.
 *
 * @tparam Float
 */
template<typename Float, typename = floating_guard<Float>>
class put_vanilla : public vanilla_template<Float> {
 public:
  /**
   * constructor.
   *
   * @param S
   * @param K
   * @param T
   * @param r
   * @param q
   * @param sigma
   */
  inline explicit constexpr
  put_vanilla(Float S, Float K, Float T, Float r, Float q, Float sigma)
      : vanilla_template<Float>(S, K, T, r, q, sigma) {}

  /**
   * value of option.
   *
   * @return
   */
  inline constexpr
  Float premium() const {
    return -this->SPV() * norm_cdf(-this->d1()) + this->KPV() * norm_cdf(-this->d2());
  }

  /**
   * delta of option.
   * sensitivity of option value with respect to underlying price.
   * Delta = dV / dS
   *
   * @return
   */
  inline constexpr
  Float delta() const {
    return -exp(-this->q * this->T) * norm_cdf(-this->d1());
  }

  /**
   * theta of option.
   * sensitivity of option value with respect to time to maturity
   * Theta = dV / d tau
   *
   * @return
   */
  inline constexpr
  Float theta() const {
    return -exp(-this->q * this->T) * this->S * norm_pdf(-this->d1()) * this->sigma / 2. / sqrt(this->T)
        + this->r * this->KPV() * norm_cdf(-this->d2())
        - this->q * this->SPV() * norm_cdf(-this->d1());
  }

  /**
   * rho of option.
   * sensitivity of option value with respect to risk-free interest rate
   * Rho = dV / dr
   *
   * @return
   */
  inline constexpr
  Float rho() const {
    return -this->T * this->KPV() * norm_cdf(-this->d2());
  }

  /**
   * compute the implied volatility from the provided information,
   * and returns a plain vanilla put option instance with the computed implied volatility.
   *
   * @param S
   * @param K
   * @param T
   * @param r
   * @param q
   * @param price
   * @return
   */
  inline static constexpr
  put_vanilla<Float>
  implied(Float S, Float K, Float T, Float r, Float q, Float price) {
    return implied_newt(put_vanilla<Float>(S, K, T, r, q, CQF_DEFAULT_IMPLIED), price);
  }

 private:
  /**
   * uses newton's method to compute implied volatility.
   *
   * @param op
   * @param price
   * @return
   */
  inline static constexpr
  put_vanilla<Float>
  implied_newt(put_vanilla<Float> op, Float price) {
    return CQF_IMPLIED_ERROR_SCALE /*scaling factor to machine epsilon to compare with absolute error, this is sad*/
               * limits<Float>::epsilon() > abs(op.premium() - price)
           /*if error is acceptable*/ ? op :
           /*else*/ implied_newt(
            /*new option */ put_vanilla<Float>(op.S, op.K, op.T, op.r, op.q,
                /*new sigma*/ op.sigma - (/*func value*/op.premium() - price) / /*derivative*/ op.vega()),
            /*price unchanged*/ price);
  }
};
} // namespace cqf

#endif //CONSTEXPR_QUANTITATIVE_INCLUDE_MODEL_BLACK_SCHOLES_H_
