#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-15.h>

constexpr auto input = R"(1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581)";

TEST(Exercise15, Part1)
{
    EXPECT_EQ(40, (aoc::exercise<2021, 15, 1>(input)));
    EXPECT_EQ(613, (aoc::exercise<2021, 15, 1>(aoc::res::data_2021_15)));
}

TEST(Exercise15, Part2)
{
    EXPECT_EQ(315, (aoc::exercise<2021, 15, 2>(input)));
    EXPECT_EQ(2899, (aoc::exercise<2021, 15, 2>(aoc::res::data_2021_15)));
}
