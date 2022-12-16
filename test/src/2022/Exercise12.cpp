#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-12.h>

constexpr auto input = R"(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi)";

TEST(Exercise12, Part1)
{
    EXPECT_EQ(31, (aoc::exercise<2022, 12, 1>(input)));
    EXPECT_EQ(481, (aoc::exercise<2022, 12, 1>(aoc::res::data_2022_12)));
}

TEST(Exercise12, Part2)
{
    EXPECT_EQ(29, (aoc::exercise<2022, 12, 2>(input)));
    EXPECT_EQ(480, (aoc::exercise<2022, 12, 2>(aoc::res::data_2022_12)));
}
