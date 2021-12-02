#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-02.h>

constexpr auto input = R"(forward 5
down 5
forward 8
up 3
down 8
forward 2)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(150, (aoc::exercise<2021, 2, 1>(input)));
    EXPECT_EQ(1636725, (aoc::exercise<2021, 2, 1>(aoc::res::data_2021_02)));
}

TEST(Exercise2, Part2)
{
    EXPECT_EQ(900, (aoc::exercise<2021, 2, 2>(input)));
    EXPECT_EQ(1872757425, (aoc::exercise<2021, 2, 2>(aoc::res::data_2021_02)));
}
