#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-02.h>

constexpr auto input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(2, (aoc::exercise<2020, 2, 1>(input)));
    EXPECT_EQ(538, (aoc::exercise<2020, 2, 1>(aoc::res::data_2020_02)));
}

TEST(Exercise2, Part2)
{
    EXPECT_EQ(1, (aoc::exercise<2020, 2, 2>(input)));
    EXPECT_EQ(489, (aoc::exercise<2020, 2, 2>(aoc::res::data_2020_02)));
}
