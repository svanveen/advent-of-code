#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise07.h>

constexpr auto input = R"(light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
)";

TEST(Exercise7, Part1)
{
    EXPECT_EQ(4, solve(event2020::exercise7::part1, input));
}

TEST(Exercise7, Part2)
{
    EXPECT_EQ(6, solve(event2020::exercise7::part2, input));
}
