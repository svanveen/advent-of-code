#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2022/Data-07.h>

constexpr auto input = R"($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)";

TEST(Exercise7, Part1)
{
    EXPECT_EQ(95437, (aoc::exercise<2022, 7, 1>(input)));
    EXPECT_EQ(1315285, (aoc::exercise<2022, 7, 1>(aoc::res::data_2022_07)));
}

TEST(Exercise7, Part2)
{
    EXPECT_EQ(24933642, (aoc::exercise<2022, 7, 2>(input)));
    EXPECT_EQ(9847279, (aoc::exercise<2022, 7, 2>(aoc::res::data_2022_07)));
}
