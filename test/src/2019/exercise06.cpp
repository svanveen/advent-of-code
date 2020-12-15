#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

TEST(Exercise6, Part1)
{
    constexpr auto input = R"(COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L
)";
    EXPECT_EQ(42, solve(aoc::exercise<2019, 6, 1>, input));
}

TEST(Exercise6, Part2)
{
    constexpr auto input = R"(COM)B
B)C
C)D
D)E
E)F
B)G
G)H
D)I
E)J
J)K
K)L
K)YOU
I)SAN
)";
    EXPECT_EQ(4, solve(aoc::exercise<2019, 6, 2>, input));
}

