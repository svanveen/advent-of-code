#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise05.h>

TEST(Exercise5, Part1)
{
    constexpr auto input = R"(BFFFBBFRRR
FFFBBBFRRR
BBFFBBFRLL
)";
    EXPECT_EQ(820, solve(event2020::exercise5::part1, input));
}
