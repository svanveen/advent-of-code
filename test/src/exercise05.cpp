#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercise05.h>

TEST(Exercise5, Part1)
{
    constexpr auto input = R"(BFFFBBFRRR
FFFBBBFRRR
BBFFBBFRLL
)";
    EXPECT_EQ(820, solve(exercise5::part1, input));
}
