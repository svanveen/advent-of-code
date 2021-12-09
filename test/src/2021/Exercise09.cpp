#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-09.h>

constexpr auto input = R"(2199943210
3987894921
9856789892
8767896789
9899965678)";

TEST(Exercise9, Part1)
{
    EXPECT_EQ(15, (aoc::exercise<2021, 9, 1>(input)));
    EXPECT_EQ(554, (aoc::exercise<2021, 9, 1>(aoc::res::data_2021_09)));
}

TEST(Exercise9, Part2)
{
    EXPECT_EQ(1134, (aoc::exercise<2021, 9, 2>(input)));
    EXPECT_EQ(1017792, (aoc::exercise<2021, 9, 2>(aoc::res::data_2021_09)));
}
