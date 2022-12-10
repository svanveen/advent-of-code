#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-05.h>

using namespace std::string_view_literals;
constexpr auto input = R"(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)"sv;

TEST(Exercise5, Part1)
{
    EXPECT_EQ("CMZ", (aoc::exercise<2022, 5, 1>(input)));
    EXPECT_EQ("TWSGQHNHL", (aoc::exercise<2022, 5, 1>(aoc::res::data_2022_05)));
}

TEST(Exercise5, Part2)
{
    EXPECT_EQ("MCD", (aoc::exercise<2022, 5, 2>(input)));
    EXPECT_EQ("JNRSCDWPP", (aoc::exercise<2022, 5, 2>(aoc::res::data_2022_05)));
}
