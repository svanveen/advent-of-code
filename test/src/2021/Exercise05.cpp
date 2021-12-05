#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-05.h>

constexpr auto input = R"(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2)";

TEST(Exercise5, Part1)
{
    EXPECT_EQ(5, (aoc::exercise<2021, 5, 1>(input)));
    EXPECT_EQ(5774, (aoc::exercise<2021, 5, 1>(aoc::res::data_2021_05)));
}

TEST(Exercise5, Part2)
{
    EXPECT_EQ(12, (aoc::exercise<2021, 5, 2>(input)));
    EXPECT_EQ(18423, (aoc::exercise<2021, 5, 2>(aoc::res::data_2021_05)));
}
