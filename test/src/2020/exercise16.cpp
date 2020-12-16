#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12
)";

TEST(Exercise16, Part1)
{
    EXPECT_EQ(71, solve(aoc::exercise<2020, 16, 1>, input));
}
