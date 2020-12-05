#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise02.h>

constexpr auto input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(2, solve(event2020::exercise2::part1, input ));
}

TEST(Exercise2, Part2)
{
    EXPECT_EQ(1, solve(event2020::exercise2::part2, input));
}
