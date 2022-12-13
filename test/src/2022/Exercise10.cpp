#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-10.h>

constexpr auto input = R"(addx 15
addx -11
addx 6
addx -3
addx 5
addx -1
addx -8
addx 13
addx 4
noop
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx -35
addx 1
addx 24
addx -19
addx 1
addx 16
addx -11
noop
noop
addx 21
addx -15
noop
noop
addx -3
addx 9
addx 1
addx -3
addx 8
addx 1
addx 5
noop
noop
noop
noop
noop
addx -36
noop
addx 1
addx 7
noop
noop
noop
addx 2
addx 6
noop
noop
noop
noop
noop
addx 1
noop
noop
addx 7
addx 1
noop
addx -13
addx 13
addx 7
noop
addx 1
addx -33
noop
noop
noop
addx 2
noop
noop
noop
addx 8
noop
addx -1
addx 2
addx 1
noop
addx 17
addx -9
addx 1
addx 1
addx -3
addx 11
noop
noop
addx 1
noop
addx 1
noop
noop
addx -13
addx -19
addx 1
addx 3
addx 26
addx -30
addx 12
addx -1
addx 3
addx 1
noop
noop
noop
addx -9
addx 18
addx 1
addx 2
noop
noop
addx 9
noop
noop
noop
addx -1
addx 2
addx -37
addx 1
addx 3
noop
addx 15
addx -21
addx 22
addx -6
addx 1
noop
addx 2
addx 1
noop
addx -10
noop
noop
addx 20
addx 1
addx 2
addx 2
addx -6
addx -11
noop
noop
noop)";

TEST(Exercise10, Part1)
{
    EXPECT_EQ(13140, (aoc::exercise<2022, 10, 1>(input)));
    EXPECT_EQ(14620, (aoc::exercise<2022, 10, 1>(aoc::res::data_2022_10)));
}

TEST(Exercise10, Part2)
{
    {
        const auto expected = R"(##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....
)"s;
        EXPECT_EQ(expected, (aoc::exercise<2022, 10, 2>(input)));
    }

    {
        const auto expected = R"(###....##.####.###..#..#.###..####.#..#.
#..#....#.#....#..#.#..#.#..#.#....#..#.
###.....#.###..#..#.####.#..#.###..#..#.
#..#....#.#....###..#..#.###..#....#..#.
#..#.#..#.#....#.#..#..#.#.#..#....#..#.
###...##..#....#..#.#..#.#..#.#.....##..
)"s;
        EXPECT_EQ(expected, (aoc::exercise<2022, 10, 2>(aoc::res::data_2022_10)));
    }
}
