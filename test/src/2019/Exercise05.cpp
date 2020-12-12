#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/2019/IntCodeProgram.h>
#include <aoc/res/2019/Data-05.h>

auto runProgram(const std::string& input, int inputValue)
{
    std::stringstream stream{input};
    aoc::IntCodeProgram prog{stream};
    return prog(inputValue);
}

TEST(Exercise5, Part1)
{
    EXPECT_EQ(7839346, (aoc::exercise<2019, 5, 1>(aoc::res::data_2019_05)));
}

TEST(Exercise5, Part2)
{
    // equal position mode
    {
        constexpr auto input = R"(3,9,8,9,10,9,4,9,99,-1,8)";
        EXPECT_FALSE(runProgram(input, 7));
        EXPECT_TRUE(runProgram(input, 8));
        EXPECT_FALSE(runProgram(input, 9));
    }
    // equal immediate mode
    {
        constexpr auto input = R"(3,3,1108,-1,8,3,4,3,99)";
        EXPECT_FALSE(runProgram(input, 7));
        EXPECT_TRUE(runProgram(input, 8));
        EXPECT_FALSE(runProgram(input, 9));
    }

    // less than position mode
    {
        constexpr auto input = R"(3,9,7,9,10,9,4,9,99,-1,8)";
        EXPECT_TRUE(runProgram(input, 7));
        EXPECT_FALSE(runProgram(input, 8));
        EXPECT_FALSE(runProgram(input, 9));
    }
    // less than immediate mode
    {
        constexpr auto input = R"(3,3,1107,-1,8,3,4,3,99)";
        EXPECT_TRUE(runProgram(input, 7));
        EXPECT_FALSE(runProgram(input, 8));
        EXPECT_FALSE(runProgram(input, 9));
    }

    // jump position mode
    {
        constexpr auto input = R"(3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9)";
        EXPECT_TRUE(runProgram(input, -1));
        EXPECT_FALSE(runProgram(input, 0));
        EXPECT_TRUE(runProgram(input, 1));
    }
    // jump immediate mode
    {
        constexpr auto input = R"(3,3,1105,-1,9,1101,0,0,12,4,12,99,1)";
        EXPECT_TRUE(runProgram(input, -1));
        EXPECT_FALSE(runProgram(input, 0));
        EXPECT_TRUE(runProgram(input, 1));
    }

    // jump
    {
        constexpr auto input = R"(3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99)";
        EXPECT_EQ(999, runProgram(input, 7));
        EXPECT_EQ(1000, runProgram(input, 8));
        EXPECT_EQ(1001, runProgram(input, 9));
    }

    EXPECT_EQ(447803, (aoc::exercise<2019, 5, 2>(aoc::res::data_2019_05)));
}

