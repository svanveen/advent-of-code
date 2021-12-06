#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-06.h>

constexpr auto input = R"(3,4,3,1,2)";

TEST(Exercise6, Part1)
{
    EXPECT_EQ(5934, (aoc::exercise<2021, 6, 1>(input)));
    EXPECT_EQ(360761, (aoc::exercise<2021, 6, 1>(aoc::res::data_2021_06)));
}

TEST(Exercise6, Part2)
{
    EXPECT_EQ(26984457539, (aoc::exercise<2021, 6, 2>(input)));
    EXPECT_EQ(1632779838045, (aoc::exercise<2021, 6, 2>(aoc::res::data_2021_06)));
}
