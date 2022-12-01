#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-01.h>

constexpr auto input = R"(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
)";

TEST(Exercise1, Part1)
{
    EXPECT_EQ(24000, (aoc::exercise<2022, 1, 1>(input)));
    EXPECT_EQ(72478, (aoc::exercise<2022, 1, 1>(aoc::res::data_2022_01)));
}

TEST(Exercise1, Part2)
{
    EXPECT_EQ(45000, (aoc::exercise<2022, 1, 2>(input)));
    EXPECT_EQ(210367, (aoc::exercise<2022, 1, 2>(aoc::res::data_2022_01)));
}
