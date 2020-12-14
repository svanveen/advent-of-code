#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
)";

TEST(Exercise14, Part1)
{
    EXPECT_EQ(165, solve(aoc::exercise<2020, 14 ,1>, input));
}

TEST(Exercise14, Part2)
{
}
