#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-12.h>

constexpr auto input = R"(F10
N3
F7
R90
F11
)";

TEST(Exercise12, Part1)
{
    EXPECT_EQ(25, (aoc::exercise<2020, 12, 1>(input)));
    EXPECT_EQ(858, (aoc::exercise<2020, 12, 1>(aoc::res::data_2020_12)));
}

TEST(Exercise12, Part2)
{
    EXPECT_EQ(286, (aoc::exercise<2020, 12, 2>(input)));
    EXPECT_EQ(39140, (aoc::exercise<2020, 12, 2>(aoc::res::data_2020_12)));
}
