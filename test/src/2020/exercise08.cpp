#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6
)";

TEST(Exercise8, Part1)
{
    EXPECT_EQ(5, solve(aoc::exercise<2020, 8, 1>, input));
}

TEST(Exercise8, Part2)
{
    EXPECT_EQ(8, solve(aoc::exercise<2020, 8, 2>, input));
}
