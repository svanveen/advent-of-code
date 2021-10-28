#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-08.h>

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
    EXPECT_EQ(5, (aoc::exercise<2020, 8, 1>(input)));
    EXPECT_EQ(1810, (aoc::exercise<2020, 8, 1>(aoc::res::data_2020_08)));
}

TEST(Exercise8, Part2)
{
    EXPECT_EQ(8, (aoc::exercise<2020, 8, 2>(input)));
    EXPECT_EQ(969, (aoc::exercise<2020, 8, 2>(aoc::res::data_2020_08)));
}
