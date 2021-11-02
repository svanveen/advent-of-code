#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-17.h>

constexpr auto input = R"(.#.
..#
###
)";

TEST(Exercise17, Part1)
{
    EXPECT_EQ(112, (aoc::exercise<2020, 17, 1>(input)));
    EXPECT_EQ(448, (aoc::exercise<2020, 17, 1>(aoc::res::data_2020_17)));
}

TEST(Exercise17, Part2)
{
    EXPECT_EQ(848, (aoc::exercise<2020, 17, 2>(input)));
    EXPECT_EQ(2400, (aoc::exercise<2020, 17, 2>(aoc::res::data_2020_17)));
}
