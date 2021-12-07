#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-07.h>

constexpr auto input = R"(16,1,2,0,4,2,7,1,2,14)";

TEST(Exercise7, Part1)
{
    EXPECT_EQ(37, (aoc::exercise<2021, 7, 1>(input)));
    EXPECT_EQ(356958, (aoc::exercise<2021, 7, 1>(aoc::res::data_2021_07)));
}

TEST(Exercise7, Part2)
{
    EXPECT_EQ(168, (aoc::exercise<2021, 7, 2>(input)));
    EXPECT_EQ(105461913, (aoc::exercise<2021, 7, 2>(aoc::res::data_2021_07)));
}
