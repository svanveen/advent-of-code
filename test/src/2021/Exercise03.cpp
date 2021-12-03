#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-03.h>

constexpr auto input = R"(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010)";

TEST(Exercise3, Part1)
{
    EXPECT_EQ(198, (aoc::exercise<2021, 3, 1>(input)));
    EXPECT_EQ(3374136, (aoc::exercise<2021, 3, 1>(aoc::res::data_2021_03)));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(230, (aoc::exercise<2021, 3, 2>(input)));
    EXPECT_EQ(4432698, (aoc::exercise<2021, 3, 2>(aoc::res::data_2021_03)));
}
