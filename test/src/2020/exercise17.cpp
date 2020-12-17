#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(.#.
..#
###
)";

TEST(Exercise17, Part1)
{
    EXPECT_EQ(112, solve(aoc::exercise<2020, 17, 1>, input));
}

TEST(Exercise17, Part2)
{
    EXPECT_EQ(848, solve(aoc::exercise<2020, 17, 2>, input));
}
