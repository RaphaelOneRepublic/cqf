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
#include "math/sin.h"

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
  // TODO

}
#pragma clang diagnostic pop