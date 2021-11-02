#include <gtest/gtest.h>
#include <aoc/exercise.h>
#include <aoc/res/2020/Data-15.h>

TEST(Exercise15, Part1)
{
    {
        constexpr auto input = R"(0,3,6)";
        EXPECT_EQ(436, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(1,3,2)";
        EXPECT_EQ(1, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(2,1,3)";
        EXPECT_EQ(10, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(1,2,3)";
        EXPECT_EQ(27, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(2,3,1)";
        EXPECT_EQ(78, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(3,2,1)";
        EXPECT_EQ(438, (aoc::exercise<2020, 15, 1>(input)));
    }
    {
        constexpr auto input = R"(3,1,2)";
        EXPECT_EQ(1836, (aoc::exercise<2020, 15, 1>(input)));
    }
    EXPECT_EQ(866, (aoc::exercise<2020, 15, 1>(aoc::res::data_2020_15)));
}

#if 0 // This take way to long
TEST(Exercise15, Part2)
{
    {
        constexpr auto input = R"(0,3,6)";
        EXPECT_EQ(175594, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(1,3,2)";
        EXPECT_EQ(2578, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(2,1,3)";
        EXPECT_EQ(3544142, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(1,2,3)";
        EXPECT_EQ(261214, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(2,3,1)";
        EXPECT_EQ(6895259, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(3,2,1)";
        EXPECT_EQ(18, (aoc::exercise<2020, 15, 2>(input)));
    }
    {
        constexpr auto input = R"(3,1,2)";
        EXPECT_EQ(362, (aoc::exercise<2020, 15, 2>(input)));
    }
    EXPECT_EQ(1437692, (aoc::exercise<2020, 15, 2>(aoc::res::data_2020_15)));
}
#endif
