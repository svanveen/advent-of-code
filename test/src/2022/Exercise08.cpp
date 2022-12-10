#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-08.h>

constexpr auto input = R"(30373
25512
65332
33549
35390)";

TEST(Exercise8, Part1)
{
    EXPECT_EQ(21, (aoc::exercise<2022, 8, 1>(input)));
    EXPECT_EQ(1832, (aoc::exercise<2022, 8, 1>(aoc::res::data_2022_08)));
}

TEST(Exercise8, Part2)
{
    EXPECT_EQ(8, (aoc::exercise<2022, 8, 2>(input)));
    EXPECT_EQ(0, (aoc::exercise<2022, 8, 2>(aoc::res::data_2022_08)));
}
