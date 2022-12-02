#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-02.h>

constexpr auto input = R"(A Y
B X
C Z)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(15, (aoc::exercise<2022, 2, 1>(input)));
    EXPECT_EQ(13809, (aoc::exercise<2022, 2, 1>(aoc::res::data_2022_02)));
}

TEST(Exercise2, Part2)
{
    EXPECT_EQ(12, (aoc::exercise<2022, 2, 2>(input)));
    EXPECT_EQ(12316, (aoc::exercise<2022, 2, 2>(aoc::res::data_2022_02)));
}
