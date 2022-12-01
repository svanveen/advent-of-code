#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-01.h>

constexpr auto input = R"()";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(0, (aoc::exercise<2022, 1, 1>(input)));
    EXPECT_EQ(0, (aoc::exercise<2022, 1, 1>(aoc::res::data_2022_01)));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(0, (aoc::exercise<2022, 1, 2>(input)));
    EXPECT_EQ(0, (aoc::exercise<2022, 1, 2>(aoc::res::data_2022_01)));
}
