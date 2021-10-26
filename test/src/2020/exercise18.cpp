#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-18.h>

constexpr auto input = R"(1 + 2 * 3 + 4 * 5 + 6
1 + (2 * 3) + (4 * (5 + 6))
2 * 3 + (4 * 5)
5 + (8 * 3 + 9 + 3 * 4 * 3)
5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))
((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2
)";

TEST(Exercise18, Part1)
{
    EXPECT_EQ(26457, (aoc::exercise<2020, 18, 1>(input)));
    EXPECT_EQ(1408133923393, (aoc::exercise<2020, 18, 1>(aoc::res::data_2020_18)));
}

TEST(Exercise18, Part2)
{
    EXPECT_EQ(694173, (aoc::exercise<2020, 18, 2>(input)));
    EXPECT_EQ(314455761823725, (aoc::exercise<2020, 18, 2>(aoc::res::data_2020_18)));
}
