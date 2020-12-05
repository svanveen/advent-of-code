#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-01.h>

TEST(Exercise1, Part1)
{
    constexpr auto input = R"(
12
14
1969
100756
)";

    EXPECT_EQ(34241, (aoc::exercise<2019, 1, 1>(input)));
    EXPECT_EQ(3550236, (aoc::exercise<2019, 1, 1>(aoc::res::data_2019_01)));
}

TEST(Exercise1, Part2)
{
    constexpr auto input = R"(
14
1969
100756
)";

    EXPECT_EQ(51314, (aoc::exercise<2019, 1, 2>(input)));
    EXPECT_EQ(5322455, (aoc::exercise<2019, 1, 2>(aoc::res::data_2019_01)));
}

