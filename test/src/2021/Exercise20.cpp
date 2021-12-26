#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-20.h>

constexpr auto input = R"(..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#

#..#.
#....
##..#
..#..
..###)";

TEST(Exercise20, Part1)
{
    EXPECT_EQ(35, (aoc::exercise<2021, 20, 1>(input)));
    EXPECT_EQ(5225, (aoc::exercise<2021, 20, 1>(aoc::res::data_2021_20)));
}

TEST(Exercise20, Part2)
{
    EXPECT_EQ(3351, (aoc::exercise<2021, 20, 2>(input)));
    EXPECT_EQ(0, (aoc::exercise<2021, 20, 2>(aoc::res::data_2021_20)));
}