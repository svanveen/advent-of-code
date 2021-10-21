#include <gtest/gtest.h>
#include <aoc/exercises.h>

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
}

TEST(Exercise6, Part2)
{
    EXPECT_EQ(6, (aoc::exercise<2020, 6, 2>(input)));
}
