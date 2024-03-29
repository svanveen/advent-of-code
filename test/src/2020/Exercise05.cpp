#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-05.h>

TEST(Exercise5, Part1)
{
    constexpr auto input = R"(BFFFBBFRRR
FFFBBBFRRR
BBFFBBFRLL
)";
    EXPECT_EQ(820, (aoc::exercise<2020, 5, 1>(input)));
    EXPECT_EQ(885, (aoc::exercise<2020, 5, 1>(aoc::res::data_2020_05)));
}

TEST(Exercise5, Part2)
{
    EXPECT_EQ(623, (aoc::exercise<2020, 5, 2>(aoc::res::data_2020_05)));
}
