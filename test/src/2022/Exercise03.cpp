#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-03.h>

constexpr auto input = R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";

TEST(Exercise3, Part1)
{
    EXPECT_EQ(157, (aoc::exercise<2022, 3, 1>(input)));
    EXPECT_EQ(8185, (aoc::exercise<2022, 3, 1>(aoc::res::data_2022_03)));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(70, (aoc::exercise<2022, 3, 2>(input)));
    EXPECT_EQ(2817, (aoc::exercise<2022, 3, 2>(aoc::res::data_2022_03)));
}
