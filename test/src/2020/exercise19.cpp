#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

constexpr auto input = R"(0: 4 1 5
1: 2 3 | 3 2
2: 4 4 | 5 5
3: 4 5 | 5 4
4: "a"
5: "b"

ababbb
bababa
abbbab
aaabbb
aaaabbb
)";

TEST(Exercise19, Part1)
{
    EXPECT_EQ(2, solve(aoc::exercise<2020, 19, 1>, input));
}
