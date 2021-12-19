#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-17.h>

constexpr auto input = R"(target area: x=20..30, y=-10..-5)";

TEST(Exercise17, Part1)
{
    EXPECT_EQ(45, (aoc::exercise<2021, 17, 1>(input)));
    EXPECT_EQ(13041, (aoc::exercise<2021, 17, 1>(aoc::res::data_2021_17)));
}

TEST(Exercise17, Part2)
{
    EXPECT_EQ(112, (aoc::exercise<2021, 17, 2>(input)));
    EXPECT_EQ(1031, (aoc::exercise<2021, 17, 2>(aoc::res::data_2021_17)));
}
