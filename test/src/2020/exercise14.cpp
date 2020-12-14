#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

TEST(Exercise14, Part1)
{
    constexpr auto input = R"(mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
)";
    EXPECT_EQ(165, solve(aoc::exercise<2020, 14 ,1>, input));
}

TEST(Exercise14, Part2)
{
    constexpr auto input = R"(mask = 000000000000000000000000000000X1001X
mem[42] = 100
mask = 00000000000000000000000000000000X0XX
mem[26] = 1
)";
    EXPECT_EQ(208, solve(aoc::exercise<2020, 14 ,2>, input));
}
