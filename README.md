# Constexpr Quant Finance
It is quite a disappointment that the C++ standard library does not mark the standard math functions as `constexpr` functions.
While implementing several quant finance models, it is inconvenient to perform explicitly compile-time computations.
Modern C++ compilers like *gcc* do usually mark the standard functions as `constexpr`, and there are an abundance of compile-time math libraries in case the compiler does not.
However, I personally find the implementation of computational methods inspiring and fun, and therewith this repo, implying that this is not to be regarded as something useful in production.

This repo implements basic math functions and some quant finance models at compile time.
Ideally, there will be zero runtime overhead.
Currently, the functionality is minimal and barely supports the computation of plain vanilla European options

## Overview
1. Basic Math Functions
`abs`, `ceil`, `floor`, `round`, `fraction`,`odd`,`even`,`nan`,`max`,`min`,
2. Taylor expansion for quickly converging Taylor series
`sin`, `cos`, `erf`
3. Newton-Raphson's for quick convergence
`sqrt`, `exp`,`ln` (each a combination of Newton's for slowly convergent portion and Taylor's for quickly convergent portion)
4. Bisection method for computing integral powers, `power`
5. Generalized Gamma functions, `gamma`, (TODO)
6. Simpson's for computing analytically insolvable integrals (TODO)
7. Black-Scholes model and Greeks (TODO)

## Typing
Since the entire library is templated, a mechanism is used to maintain type relationships.
Two meta-functions are used for guarding against floating-point / integral type misuse:
`integral_guard` & `floating_guard`.
Every numeric type has an implicit floating point type. For floating point types, these refer back to themselves. For integral types, this refers to `double`.
This is known in the code as a promoted type `promoted<Numeric>`. For functions that accept integral types where the context makes it clear that floating point types are required, the accepted type is promoted to the implicit type.
