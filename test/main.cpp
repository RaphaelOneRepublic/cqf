#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-flp30-c"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

#include "math/traits.h"
#include "math/basic.h"
#include "math/power.h"
#include "math/exp.h"
#include "math/log.h"
#include "math/sqrt.h"
#include "math/erf.h"
#include "math/trig.h"
#include "math/gcd.h"
#include "math/norm.h"

#include "model/black_scholes.h"

class TestSuite :
    public ::testing::Test {
 protected:
  void SetUp() override {
    Test::SetUp();
  }
  void TearDown() override {
    Test::TearDown();
  }
};

TEST_F(TestSuite, main) {
  cqf::vanilla option(100., 100., 1., 0.05, 0.3);
  std::cout << option.premium() << std::endl;
}
#pragma clang diagnostic pop