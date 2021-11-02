#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-11.h>

constexpr auto input = R"(L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL
)";

TEST(Exercise11, Part1)
{
    EXPECT_EQ(37, (aoc::exercise<2020, 11, 1>(input)));
    EXPECT_EQ(2334, (aoc::exercise<2020, 11, 1>(aoc::res::data_2020_11)));
}

TEST(Exercise11, Part2)
{
    EXPECT_EQ(26, (aoc::exercise<2020, 11, 2>(input)));
    EXPECT_EQ(2100, (aoc::exercise<2020, 11, 2>(aoc::res::data_2020_11)));
}
