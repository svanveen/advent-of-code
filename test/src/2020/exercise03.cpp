#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/2020/exercise03.h>

constexpr auto input = R"(..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#
)";

TEST(Exercise3, Part1)
{
    EXPECT_EQ(7, solve(event2020::exercise3::part1, input));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(336, solve(event2020::exercise3::part2, input));
}

