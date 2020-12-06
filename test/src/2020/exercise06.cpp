#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise06.h>

TEST(Exercise6, Part1)
{
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
    EXPECT_EQ(11, solve(event2020::exercise6::part1, input));
}
