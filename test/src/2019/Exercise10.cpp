#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-10.h>

constexpr auto input0 = R"(.#..#
.....
#####
....#
...##)";

constexpr auto input1 = R"(......#.#.
#..#.#....
..#######.
.#.#.###..
.#..#.....
..#....#.#
#..#....#.
.##.#..###
##...#..#.
.#....####)";

constexpr auto input2 = R"(#.#...#.#.
.###....#.
.#....#...
##.#.#.#.#
....#.#.#.
.##..###.#
..#...##..
..##....##
......#...
.####.###.)";

constexpr auto input3 = R"(.#..#..###
####.###.#
....###.#.
..###.##.#
##.##.#.#.
....###..#
..#.#..#.#
#..#.#.###
.##...##.#
.....#.#..)";

constexpr auto input4 = R"(.#..##.###...#######
##.############..##.
.#.######.########.#
.###.#######.####.#.
#####.##.#.##.###.##
..#####..#.#########
####################
#.####....###.#.#.##
##.#################
#####.##.###..####..
..######..##.#######
####.##.####...##..#
.#####..#.######.###
##...#.##########...
#.##########.#######
.####.#.###.###.#.##
....##.##.###..#####
.#.#.###########.###
#.#.#.#####.####.###
###.##.####.##.#..##)";



TEST(Exercise10, Part1)
{
    EXPECT_EQ(8, (aoc::exercise<2019, 10, 1>(input0)));
    EXPECT_EQ(33, (aoc::exercise<2019, 10, 1>(input1)));
    EXPECT_EQ(35, (aoc::exercise<2019, 10, 1>(input2)));
    EXPECT_EQ(41, (aoc::exercise<2019, 10, 1>(input3)));
    EXPECT_EQ(210, (aoc::exercise<2019, 10, 1>(input4)));
    EXPECT_EQ(319, (aoc::exercise<2019, 10, 1>(aoc::res::data_2019_10)));
}

TEST(Exercise10, Part2)
{
    EXPECT_EQ(802, (aoc::exercise<2019, 10, 2>(input4)));
    EXPECT_EQ(0, (aoc::exercise<2019, 10, 2>(aoc::res::data_2019_10)));
}