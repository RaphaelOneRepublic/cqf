cmake_minimum_required(VERSION 3.10)
project(constexpr_quantitative)
set(CMAKE_CXX_STANDARD 17)

add_library(
        cqf include/cqf.cpp
        include/math/traits.h
        include/math/constants.h
        include/math/basic.h
        include/math/power.h
        include/math/exp.h
        include/math/log.h
        include/math/sqrt.h include/math/erf.h include/math/gamma.h include/math/trig.h include/math/gcd.h include/math/norm.h include/model/black_scholes.h)
target_include_directories(cqf PUBLIC include)

enable_testing()
find_package(GTest)
add_executable(main test/main.cpp)
target_link_libraries(main cqf ${GTEST_BOTH_LIBRARIES} pthread)