#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

constexpr auto input = R"(1,9,10,3,2,3,11,0,99,30,40,50)";

TEST(Exercise2, Part1)
{
    std::stringstream stream{input};
    const aoc::IntCodeProgram prog{stream};
    EXPECT_EQ(3500, prog(9, 10));
}

