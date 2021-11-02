#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-01.h>

constexpr auto input = R"(
1721
979
366
299
675
1456
)";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(514579, (aoc::exercise<2020, 1, 1>(input)));
    EXPECT_EQ(197451, (aoc::exercise<2020, 1, 1>(aoc::res::data_2020_01)));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(241861950, (aoc::exercise<2020, 1, 2>(input)));
    EXPECT_EQ(138233720, (aoc::exercise<2020, 1, 2>(aoc::res::data_2020_01)));
}

