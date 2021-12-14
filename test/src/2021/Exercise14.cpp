#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-14.h>

constexpr auto input = R"(NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C)";

TEST(Exercise14, Part1)
{
    EXPECT_EQ(1588, (aoc::exercise<2021, 14, 1>(input)));
    EXPECT_EQ(3247, (aoc::exercise<2021, 14, 1>(aoc::res::data_2021_14)));
}

TEST(Exercise14, Part2)
{
    EXPECT_EQ(2188189693529, (aoc::exercise<2021, 14, 2>(input)));
    EXPECT_EQ(0, (aoc::exercise<2021, 14, 2>(aoc::res::data_2021_14)));
}
