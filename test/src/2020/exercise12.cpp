#include <gtest/gtest.h>
#include <aoc/exercises.h>

constexpr auto input = R"(F10
N3
F7
R90
F11
)";

TEST(Exercise12, Part1)
{
    EXPECT_EQ(25, (aoc::exercise<2020, 12 ,1>(input)));
}

TEST(Exercise12, Part2)
{
    EXPECT_EQ(286, (aoc::exercise<2020, 12 ,2>(input)));
}
