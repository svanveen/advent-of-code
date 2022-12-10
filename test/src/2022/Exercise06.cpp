#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-06.h>

constexpr auto input0 = R"(mjqjpqmgbljsphdztnvjfqwrcgsmlb)";
constexpr auto input1 = R"(bvwbjplbgvbhsrlpgdmjqwftvncz)";
constexpr auto input2 = R"(nppdvjthqldpwncqszvftbrmjlhg)";
constexpr auto input3 = R"(nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg)";
constexpr auto input4 = R"(zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw)";

TEST(Exercise6, Part1)
{
    EXPECT_EQ(7, (aoc::exercise<2022, 6, 1>(input0)));
    EXPECT_EQ(5, (aoc::exercise<2022, 6, 1>(input1)));
    EXPECT_EQ(6, (aoc::exercise<2022, 6, 1>(input2)));
    EXPECT_EQ(10, (aoc::exercise<2022, 6, 1>(input3)));
    EXPECT_EQ(11, (aoc::exercise<2022, 6, 1>(input4)));
    EXPECT_EQ(1920, (aoc::exercise<2022, 6, 1>(aoc::res::data_2022_06)));
}

TEST(Exercise6, Part2)
{
    EXPECT_EQ(19, (aoc::exercise<2022, 6, 2>(input0)));
    EXPECT_EQ(23, (aoc::exercise<2022, 6, 2>(input1)));
    EXPECT_EQ(23, (aoc::exercise<2022, 6, 2>(input2)));
    EXPECT_EQ(29, (aoc::exercise<2022, 6, 2>(input3)));
    EXPECT_EQ(26, (aoc::exercise<2022, 6, 2>(input4)));
    EXPECT_EQ(2334, (aoc::exercise<2022, 6, 2>(aoc::res::data_2022_06)));
}
