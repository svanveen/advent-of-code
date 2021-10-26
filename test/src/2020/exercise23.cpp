#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-23.h>

constexpr auto input = R"(389125467)";

TEST(Exercise23, Part1)
{
    EXPECT_EQ(67384529, (aoc::exercise<2020, 23, 1>(input)));
    EXPECT_EQ(46978532, (aoc::exercise<2020, 23, 1>(aoc::res::data_2020_23)));
}

TEST(Exercise23, Part2)
{
    EXPECT_EQ(149245887792, (aoc::exercise<2020, 23, 2>(input)));
    EXPECT_EQ(163035127721, (aoc::exercise<2020, 23, 2>(aoc::res::data_2020_23)));
}

