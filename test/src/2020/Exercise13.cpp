#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-13.h>

constexpr auto input = R"(939
7,13,x,x,59,x,31,19
)";

TEST(Exercise13, Part1)
{
    EXPECT_EQ(295, (aoc::exercise<2020, 13, 1>(input)));
    EXPECT_EQ(5257, (aoc::exercise<2020, 13, 1>(aoc::res::data_2020_13)));
}

TEST(Exercise13, Part2)
{
    EXPECT_EQ(1068781, (aoc::exercise<2020, 13, 2>(input)));
    EXPECT_EQ(538703333547789, (aoc::exercise<2020, 13, 2>(aoc::res::data_2020_13)));
}
