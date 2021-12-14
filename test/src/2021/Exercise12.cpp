#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-12.h>

constexpr auto input1 = R"(start-A
start-b
A-c
A-b
b-d
A-end
b-end)";

constexpr auto input2 = R"(dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc)";

constexpr auto input3 = R"(fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW)";

TEST(Exercise12, Part1)
{
    EXPECT_EQ(10, (aoc::exercise<2021, 12, 1>(input1)));
    EXPECT_EQ(19, (aoc::exercise<2021, 12, 1>(input2)));
    EXPECT_EQ(226, (aoc::exercise<2021, 12, 1>(input3)));
    EXPECT_EQ(3779, (aoc::exercise<2021, 12, 1>(aoc::res::data_2021_12)));
}

TEST(Exercise12, Part2)
{
    EXPECT_EQ(36, (aoc::exercise<2021, 12, 2>(input1)));
    EXPECT_EQ(103, (aoc::exercise<2021, 12, 2>(input2)));
    EXPECT_EQ(3509, (aoc::exercise<2021, 12, 2>(input3)));
    EXPECT_EQ(96988, (aoc::exercise<2021, 12, 2>(aoc::res::data_2021_12)));
}
