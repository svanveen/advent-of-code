#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-10.h>

constexpr auto input = R"([({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]])";

TEST(Exercise10, Part1)
{
    EXPECT_EQ(26397, (aoc::exercise<2021, 10, 1>(input)));
    EXPECT_EQ(240123, (aoc::exercise<2021, 10, 1>(aoc::res::data_2021_10)));
}

TEST(Exercise10, Part2)
{
    EXPECT_EQ(288957, (aoc::exercise<2021, 10, 2>(input)));
    EXPECT_EQ(3260812321, (aoc::exercise<2021, 10, 2>(aoc::res::data_2021_10)));
}
