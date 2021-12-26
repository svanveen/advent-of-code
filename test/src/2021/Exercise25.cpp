#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-25.h>

constexpr auto input = R"(v...>>.vv>
.vv>>.vv..
>>.>v>...v
>>v>>.>.v.
v>v.vv.v..
>.>>..v...
.vv..>.>v.
v.v..>>v.v
....v..v.>)";

TEST(Exercise25, Part1)
{
    EXPECT_EQ(58, (aoc::exercise<2021, 25, 1>(input)));
    EXPECT_EQ(560, (aoc::exercise<2021, 25, 1>(aoc::res::data_2021_25)));
}

TEST(Exercise25, Part2)
{
    EXPECT_EQ(0, (aoc::exercise<2021, 25, 2>(input)));
    EXPECT_EQ(0, (aoc::exercise<2021, 25, 2>(aoc::res::data_2021_25)));
}
