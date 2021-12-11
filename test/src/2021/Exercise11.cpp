#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-11.h>

constexpr auto input = R"(5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526)";

TEST(Exercise11, Part1)
{
    EXPECT_EQ(1656, (aoc::exercise<2021, 11, 1>(input)));
    EXPECT_EQ(1644, (aoc::exercise<2021, 11, 1>(aoc::res::data_2021_11)));
}

TEST(Exercise11, Part2)
{
    EXPECT_EQ(195, (aoc::exercise<2021, 11, 2>(input)));
    EXPECT_EQ(229, (aoc::exercise<2021, 11, 2>(aoc::res::data_2021_11)));
}
