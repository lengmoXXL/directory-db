#include "gtest/gtest.h"
#include "boost/accumulators/accumulators.hpp"
#include "boost/accumulators/statistics/min.hpp"
#include "boost/accumulators/statistics/mean.hpp"

using namespace boost::accumulators;

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

    accumulator_set<double, features< tag::min, tag::mean >> acc;
    acc(0.1);
    acc(0.2);
    acc(0.3);
    EXPECT_EQ(0.1, min(acc));
    EXPECT_DOUBLE_EQ(0.2, mean(acc));
}