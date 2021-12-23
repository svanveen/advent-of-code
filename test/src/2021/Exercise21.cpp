#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-21.h>

constexpr auto input = R"(Player 1 starting position: 4
Player 2 starting position: 8)";

TEST(Exercise21, Part1)
{
    EXPECT_EQ(739785, (aoc::exercise<2021, 21, 1>(input)));
    EXPECT_EQ(678468, (aoc::exercise<2021, 21, 1>(aoc::res::data_2021_21)));
}

TEST(Exercise21, Part2)
{
    EXPECT_EQ(444356092776315, (aoc::exercise<2021, 21, 2>(input)));
    EXPECT_EQ(131180774190079, (aoc::exercise<2021, 21, 2>(aoc::res::data_2021_21)));
}
