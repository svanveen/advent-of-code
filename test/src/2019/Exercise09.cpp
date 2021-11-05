#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/2019/IntCodeProgram.h>
#include <aoc/res/2019/Data-09.h>

constexpr auto input = R"(104,1125899906842624,99)";

auto runProgram(const std::string& input, const std::vector<long long>& inputs = {})
{
    std::stringstream stream{input};
    aoc::IntCodeProgram prog{stream};
    return prog(inputs).first;
}

TEST(Exercise9, Part1)
{
    EXPECT_EQ(1125899906842624, runProgram(input));
    EXPECT_EQ(2171728567, (aoc::exercise<2019, 9, 1>(aoc::res::data_2019_09)));
}

TEST(Exercise9, Part2)
{
    EXPECT_EQ(49815, (aoc::exercise<2019, 9, 2>(aoc::res::data_2019_09)));
}
