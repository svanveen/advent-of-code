#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-06.h>

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
    EXPECT_EQ(42, (aoc::exercise<2019, 6, 1>(input)));
    EXPECT_EQ(387356, (aoc::exercise<2019, 6, 1>(aoc::res::data_2019_06)));
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
    EXPECT_EQ(4, (aoc::exercise<2019, 6, 2>(input)));
    EXPECT_EQ(532, (aoc::exercise<2019, 6, 2>(aoc::res::data_2019_06)));
}

