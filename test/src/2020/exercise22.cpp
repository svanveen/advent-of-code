#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-22.h>

constexpr auto input = R"(Player 1:
9
2
6
3
1

Player 2:
5
8
4
7
10
)";

TEST(Exercise22, Part1)
{
    EXPECT_EQ(306, (aoc::exercise<2020, 22, 1>(input)));
    EXPECT_EQ(34127, (aoc::exercise<2020, 22, 1>(aoc::res::data_2020_22)));
}

TEST(Exercise22, Part2)
{
    EXPECT_EQ(291, (aoc::exercise<2020, 22, 2>(input)));
    EXPECT_EQ(32054, (aoc::exercise<2020, 22, 2>(aoc::res::data_2020_22)));
}

