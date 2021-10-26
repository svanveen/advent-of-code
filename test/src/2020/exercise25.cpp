#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-25.h>

constexpr auto input = R"(5764801
17807724
)";

TEST(Exercise25, Part1)
{
    EXPECT_EQ(14897079, (aoc::exercise<2020, 25, 1>(input)));
    EXPECT_EQ(2679568, (aoc::exercise<2020, 25, 1>(aoc::res::data_2020_25)));
}

TEST(Exercise25, Part2)
{
    EXPECT_TRUE(false);
}

