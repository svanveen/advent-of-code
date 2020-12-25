#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(5764801
17807724
)";

TEST(Exercise25, Part1)
{
    EXPECT_EQ(14897079, solve(aoc::exercise<2020, 25, 1>, input));
}

