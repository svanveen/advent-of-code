#include <gtest/gtest.h>
#include <aoc/exercises.h>

constexpr auto input = R"(389125467)";

TEST(Exercise23, Part1)
{
    EXPECT_EQ(67384529, (aoc::exercise<2020, 23, 1>(input)));
}

TEST(Exercise23, Part2)
{
    EXPECT_EQ(149245887792, (aoc::exercise<2020, 23, 2>(input)));
}

