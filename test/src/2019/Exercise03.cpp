#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-03.h>

constexpr auto input1 = R"(R75,D30,R83,U83,L12,D49,R71,U7,L72
U62,R66,U55,R34,D71,R55,D58,R83)";
constexpr auto input2 = R"(R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
U98,R91,D20,R16,D67,R40,U7,R15,U6,R7)";

TEST(Exercise3, Part1)
{
    EXPECT_EQ(159, (aoc::exercise<2019, 3, 1>(input1)));
    EXPECT_EQ(135, (aoc::exercise<2019, 3, 1>(input2)));
    EXPECT_EQ(721, (aoc::exercise<2019, 3, 1>(aoc::res::data_2019_03)));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(610, (aoc::exercise<2019, 3, 2>(input1)));
    EXPECT_EQ(410, (aoc::exercise<2019, 3, 2>(input2)));
    EXPECT_EQ(7388, (aoc::exercise<2019, 3, 2>(aoc::res::data_2019_03)));
}

