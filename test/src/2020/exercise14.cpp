#include <gtest/gtest.h>
#include <aoc/exercise.h>
#include <aoc/res/2020/Data-14.h>

TEST(Exercise14, Part1)
{
    constexpr auto input = R"(mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
)";
    EXPECT_EQ(165, (aoc::exercise<2020, 14, 1>(input)));
    EXPECT_EQ(14722016054794, (aoc::exercise<2020, 14, 1>(aoc::res::data_2020_14)));
}

TEST(Exercise14, Part2)
{
    constexpr auto input = R"(mask = 000000000000000000000000000000X1001X
mem[42] = 100
mask = 00000000000000000000000000000000X0XX
mem[26] = 1
)";
    EXPECT_EQ(208, (aoc::exercise<2020, 14, 2>(input)));
    EXPECT_EQ(3618217244644, (aoc::exercise<2020, 14, 2>(aoc::res::data_2020_14)));
}
