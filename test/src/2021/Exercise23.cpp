#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-23.h>

constexpr auto input = R"(#############
#...........#
###B#C#B#D###
  #A#D#C#A#
  #########)";

TEST(Exercise23, Part1)
{
    EXPECT_EQ(12521, (aoc::exercise<2021, 23, 1>(input)));
    EXPECT_EQ(14460, (aoc::exercise<2021, 23, 1>(aoc::res::data_2021_23)));
}

TEST(Exercise23, Part2)
{
    EXPECT_EQ(44169, (aoc::exercise<2021, 23, 2>(input)));
    EXPECT_EQ(41366, (aoc::exercise<2021, 23, 2>(aoc::res::data_2021_23)));
}
