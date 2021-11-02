#include <gtest/gtest.h>
#include <aoc/exercise.h>
#include <aoc/res/2020/Data-10.h>

constexpr auto input1 = R"(16
10
15
5
1
11
7
19
6
12
4
)";
constexpr auto input2 = R"(28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3
)";

TEST(Exercise10, Part1)
{
    EXPECT_EQ(35, (aoc::exercise<2020, 10, 1>(input1)));
    EXPECT_EQ(220, (aoc::exercise<2020, 10, 1>(input2)));
    EXPECT_EQ(2112, (aoc::exercise<2020, 10, 1>(aoc::res::data_2020_10)));
}

TEST(Exercise10, Part2)
{
    EXPECT_EQ(8, (aoc::exercise<2020, 10, 2>(input1)));
    EXPECT_EQ(19208, (aoc::exercise<2020, 10, 2>(input2)));
    EXPECT_EQ(3022415986688, (aoc::exercise<2020, 10, 2>(aoc::res::data_2020_10)));
}
