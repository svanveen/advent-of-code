#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-06.h>

constexpr auto input = R"(abc

a
b
c

ab
ac

a
a
a
a

b
)";

TEST(Exercise6, Part1)
{
    EXPECT_EQ(11, (aoc::exercise<2020, 6, 1>(input)));
    EXPECT_EQ(6387, (aoc::exercise<2020, 6, 1>(aoc::res::data_2020_06)));
}

TEST(Exercise6, Part2)
{
    EXPECT_EQ(6, (aoc::exercise<2020, 6, 2>(input)));
    EXPECT_EQ(3039, (aoc::exercise<2020, 6, 2>(aoc::res::data_2020_06)));
}
