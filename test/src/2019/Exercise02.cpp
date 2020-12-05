#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/2019/IntCodeProgram.h>
#include <aoc/res/2019/Data-02.h>

constexpr auto input = R"(1,9,10,3,2,3,11,0,99,30,40,50)";

TEST(Exercise2, Part1)
{
    EXPECT_EQ(4570637, (aoc::exercise<2019, 2, 1>(aoc::res::data_2019_02)));
}

TEST(Exercise2, Part2)
{
    std::stringstream stream{input};
    const aoc::IntCodeProgram prog{stream};
    EXPECT_EQ(3500, prog(9, 10));

    EXPECT_EQ(5485, (aoc::exercise<2019, 2, 2>(aoc::res::data_2019_02)));
}

