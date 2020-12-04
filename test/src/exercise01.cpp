#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercise01.h>

constexpr auto input = R"(
1721
979
366
299
675
1456
)";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(514579, solve(exercise1::part1, input));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(241861950, solve(exercise1::part2, input));
}

