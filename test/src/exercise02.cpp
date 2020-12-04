#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercise02.h>

constexpr auto input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(2, solve(exercise2::part1, input ));
}

TEST(Exercise2, Part2)
{
    EXPECT_EQ(1, solve(exercise2::part2, input));
}
