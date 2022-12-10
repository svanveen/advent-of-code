#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-04.h>

constexpr auto input = R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8)";

TEST(Exercise4, Part1)
{
    EXPECT_EQ(2, (aoc::exercise<2022, 4, 1>(input)));
    EXPECT_EQ(605, (aoc::exercise<2022, 4, 1>(aoc::res::data_2022_04)));
}

TEST(Exercise4, Part2)
{
    EXPECT_EQ(4, (aoc::exercise<2022, 4, 2>(input)));
    EXPECT_EQ(914, (aoc::exercise<2022, 4, 2>(aoc::res::data_2022_04)));
}
