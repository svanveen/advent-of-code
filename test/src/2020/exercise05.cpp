#include <gtest/gtest.h>
#include <aoc/exercises.h>

TEST(Exercise5, Part1)
{
    constexpr auto input = R"(BFFFBBFRRR
FFFBBBFRRR
BBFFBBFRLL
)";
    EXPECT_EQ(820, (aoc::exercise<2020, 5, 1>(input)));
}
