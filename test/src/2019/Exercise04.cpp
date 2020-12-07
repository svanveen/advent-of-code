#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-04.h>

TEST(Exercise4, Part1)
{
    constexpr auto input1 = R"(111111-111111)";
    EXPECT_EQ(1, (aoc::exercise<2019, 4, 1>(input1)));

    constexpr auto input2 = R"(223450-223450)";
    EXPECT_EQ(0, (aoc::exercise<2019, 4, 1>(input2)));

    constexpr auto input3 = R"(123789-123789)";
    EXPECT_EQ(0, (aoc::exercise<2019, 4, 1>(input3)));

    EXPECT_EQ(1748, (aoc::exercise<2019, 4, 1>(aoc::res::data_2019_04)));
}

TEST(Exercise4, Part2)
{
    constexpr auto input1 = R"(112233-112233)";
    EXPECT_EQ(1, (aoc::exercise<2019, 4, 2>(input1)));

    constexpr auto input2 = R"(123444-123444)";
    EXPECT_EQ(0, (aoc::exercise<2019, 4, 2>(input2)));

    constexpr auto input3 = R"(111122-111122)";
    EXPECT_EQ(1, (aoc::exercise<2019, 4, 2>(input3)));

    EXPECT_EQ(1180, (aoc::exercise<2019, 4, 2>(aoc::res::data_2019_04)));
}

