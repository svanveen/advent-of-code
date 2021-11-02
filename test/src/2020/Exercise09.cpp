#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2020/Data-09.h>

constexpr auto input = R"(35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576
)";

TEST(Exercise9, Part1)
{
    EXPECT_EQ(23278925, (aoc::exercise<2020, 9, 1>(aoc::res::data_2020_09)));
}

TEST(Exercise9, Part2)
{
    EXPECT_EQ(4011064, (aoc::exercise<2020, 9, 2>(aoc::res::data_2020_09)));
}
