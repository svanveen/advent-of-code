#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-09.h>

constexpr auto input = R"(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)";

TEST(Exercise9, Part1)
{
    EXPECT_EQ(13, (aoc::exercise<2022, 9, 1>(input)));
    EXPECT_EQ(5683, (aoc::exercise<2022, 9, 1>(aoc::res::data_2022_09)));
}

TEST(Exercise9, Part2)
{
    EXPECT_EQ(1, (aoc::exercise<2022, 9, 2>(input)));
    constexpr auto input1 = R"(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20)";
    EXPECT_EQ(36, (aoc::exercise<2022, 9, 2>(input1)));
    EXPECT_EQ(2372, (aoc::exercise<2022, 9, 2>(aoc::res::data_2022_09)));
}
