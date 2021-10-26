#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-3.h>

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
    EXPECT_EQ(7, (aoc::exercise<2020, 3, 1>(input)));
    EXPECT_EQ(176, (aoc::exercise<2020, 3, 1>(aoc::res::data_2020_3)));
}

TEST(Exercise3, Part2)
{
    EXPECT_EQ(336, (aoc::exercise<2020, 3, 2>(input)));
    EXPECT_EQ(5872458240, (aoc::exercise<2020, 3, 2>(aoc::res::data_2020_3)));
}

