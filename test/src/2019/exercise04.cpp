#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

TEST(Exercise4, Part1)
{
    constexpr auto input1 = R"(111111-111111)";
    EXPECT_EQ(1, solve(aoc::exercise<2019, 4, 1>, input1));

    constexpr auto input2 = R"(223450-223450)";
    EXPECT_EQ(0, solve(aoc::exercise<2019, 4, 1>, input2));

    constexpr auto input3 = R"(123789-123789)";
    EXPECT_EQ(0, solve(aoc::exercise<2019, 4, 1>, input3));
}

TEST(Exercise4, Part2)
{
}

