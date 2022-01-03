#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-24.h>

TEST(Exercise24, Part1)
{
    EXPECT_EQ(49917929934999, (aoc::exercise<2021, 24, 1>(aoc::res::data_2021_24)));
}

TEST(Exercise24, Part2)
{
    EXPECT_EQ(11911316711816, (aoc::exercise<2021, 24, 2>(aoc::res::data_2021_24)));
}
