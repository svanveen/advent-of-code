#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

TEST(Exercise15, Part1)
{
    {
        constexpr auto input = R"(0,3,6)";
        EXPECT_EQ(436, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(1,3,2)";
        EXPECT_EQ(1, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(2,1,3)";
        EXPECT_EQ(10, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(1,2,3)";
        EXPECT_EQ(27, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(2,3,1)";
        EXPECT_EQ(78, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(3,2,1)";
        EXPECT_EQ(438, solve(aoc::exercise<2020, 15, 1>, input));
    }
    {
        constexpr auto input = R"(3,1,2)";
        EXPECT_EQ(1836, solve(aoc::exercise<2020, 15, 1>, input));
    }
}

#if 0 // This take way to long
TEST(Exercise15, Part2)
{
    {
        constexpr auto input = R"(0,3,6)";
        EXPECT_EQ(175594, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(1,3,2)";
        EXPECT_EQ(2578, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(2,1,3)";
        EXPECT_EQ(3544142, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(1,2,3)";
        EXPECT_EQ(261214, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(2,3,1)";
        EXPECT_EQ(6895259, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(3,2,1)";
        EXPECT_EQ(18, solve(aoc::exercise<2020, 15, 2>, input));
    }
    {
        constexpr auto input = R"(3,1,2)";
        EXPECT_EQ(362, solve(aoc::exercise<2020, 15, 2>, input));
    }
}
#endif
