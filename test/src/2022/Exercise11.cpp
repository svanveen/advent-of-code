#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-11.h>

constexpr auto input = R"(Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3

Monkey 1:
  Starting items: 54, 65, 75, 74
  Operation: new = old + 6
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 2:
  Starting items: 79, 60, 97
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 3

Monkey 3:
  Starting items: 74
  Operation: new = old + 3
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 1)"sv;

TEST(Exercise11, Part1)
{
    EXPECT_EQ(10605, (aoc::exercise<2022, 11, 1>(input)));
    EXPECT_EQ(100345, (aoc::exercise<2022, 11, 1>(aoc::res::data_2022_11)));
}

TEST(Exercise11, Part2)
{
    EXPECT_EQ(2713310158, (aoc::exercise<2022, 11, 2>(input)));
    EXPECT_EQ(28537348205, (aoc::exercise<2022, 11, 2>(aoc::res::data_2022_11)));
}
