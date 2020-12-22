#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(Player 1:
9
2
6
3
1

Player 2:
5
8
4
7
10
)";

TEST(Exercise22, Part1)
{
    EXPECT_EQ(306, solve(aoc::exercise<2020, 22, 1>, input));
}

