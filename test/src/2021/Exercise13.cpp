#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-13.h>

constexpr auto input = R"(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5)";

TEST(Exercise13, Part1)
{
    EXPECT_EQ(17, (aoc::exercise<2021, 13, 1>(input)));
    EXPECT_EQ(682, (aoc::exercise<2021, 13, 1>(aoc::res::data_2021_13)));
}

TEST(Exercise13, Part2)
{
    {
        const auto expect = R"(
#####
#   #
#   #
#   #
#####)";
        EXPECT_EQ(expect, (aoc::exercise<2021, 13, 2>(input)));
    }
    {
        const auto expect = R"(
####  ##   ##  #  # ###  #### #  # ####
#    #  # #  # #  # #  #    # #  # #
###  #  # #    #  # #  #   #  #### ###
#    #### # ## #  # ###   #   #  # #
#    #  # #  # #  # # #  #    #  # #
#    #  #  ###  ##  #  # #### #  # ####)";
        EXPECT_EQ(expect, (aoc::exercise<2021, 13, 2>(aoc::res::data_2021_13)));
    }
}
