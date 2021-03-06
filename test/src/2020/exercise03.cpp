#include <gtest/gtest.h>
#include <test/util.h>
#include <aoc/exercises.h>

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
    EXPECT_EQ(7, solve(aoc::exercise<2020, 3, 1>, input));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(336, solve(aoc::exercise<2020, 3, 2>, input));
}

