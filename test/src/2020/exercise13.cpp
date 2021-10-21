#include <gtest/gtest.h>
#include <aoc/exercises.h>

constexpr auto input = R"(939
7,13,x,x,59,x,31,19
)";

TEST(Exercise13, Part1)
{
    EXPECT_EQ(295, (aoc::exercise<2020, 13 ,1>(input)));
}

TEST(Exercise13, Part2)
{
    EXPECT_EQ(1068781, (aoc::exercise<2020, 13 ,2>(input)));
}
