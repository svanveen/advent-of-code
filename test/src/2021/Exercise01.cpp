#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-01.h>

constexpr auto input = R"(199
200
208
210
200
207
240
269
260
263)";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(7, (aoc::exercise<2021, 1, 1>(input)));
    EXPECT_EQ(1477, (aoc::exercise<2021, 1, 1>(aoc::res::data_2021_01)));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(5, (aoc::exercise<2021, 1, 2>(input)));
    EXPECT_EQ(1523, (aoc::exercise<2021, 1, 2>(aoc::res::data_2021_01)));
}
