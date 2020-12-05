#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

TEST(Exercise1, Part1)
{
    constexpr auto input = R"(
12
14
1969
100756
)";

    EXPECT_EQ(34241, solve(aoc::exercise<2019, 1, 1>, input));
}

TEST(Exercise1, Part2)
{
    constexpr auto input = R"(
14
1969
100756
)";

    EXPECT_EQ(51314, solve(aoc::exercise<2019, 1, 2>, input));
}

