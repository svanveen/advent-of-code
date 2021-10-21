#include <gtest/gtest.h>
#include <aoc/exercises.h>

constexpr auto input = R"(
1721
979
366
299
675
1456
)";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(514579, (aoc::exercise<2020, 1, 1>(input)));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(241861950, (aoc::exercise<2020, 1, 2>(input)));
}

