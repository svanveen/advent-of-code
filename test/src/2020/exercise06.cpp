#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise06.h>

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
    EXPECT_EQ(11, solve(event2020::exercise6::part1, input));
}

TEST(Exercise6, Part2)
{
    EXPECT_EQ(6, solve(event2020::exercise6::part2, input));
}
