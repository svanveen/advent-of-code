#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2021/Data-16.h>

TEST(Exercise16, Part1)
{
    EXPECT_EQ(16, (aoc::exercise<2021, 16, 1>("8A004A801A8002F478")));
    EXPECT_EQ(12, (aoc::exercise<2021, 16, 1>("620080001611562C8802118E34")));
    EXPECT_EQ(23, (aoc::exercise<2021, 16, 1>("C0015000016115A2E0802F182340")));
    EXPECT_EQ(31, (aoc::exercise<2021, 16, 1>("A0016C880162017C3686B18A3D4780")));
    EXPECT_EQ(943, (aoc::exercise<2021, 16, 1>(aoc::res::data_2021_16)));
}

TEST(Exercise16, Part2)
{
    EXPECT_EQ(3, (aoc::exercise<2021, 16, 2>("C200B40A82")));
    EXPECT_EQ(54, (aoc::exercise<2021, 16, 2>("04005AC33890")));
    EXPECT_EQ(7, (aoc::exercise<2021, 16, 2>("880086C3E88112")));
    EXPECT_EQ(9, (aoc::exercise<2021, 16, 2>("CE00C43D881120")));
    EXPECT_EQ(1, (aoc::exercise<2021, 16, 2>("D8005AC2A8F0")));
    EXPECT_EQ(0, (aoc::exercise<2021, 16, 2>("F600BC2D8F")));
    EXPECT_EQ(0, (aoc::exercise<2021, 16, 2>("9C005AC2F8F0")));
    EXPECT_EQ(1, (aoc::exercise<2021, 16, 2>("9C0141080250320F1802104A08")));
    EXPECT_EQ(167737115857, (aoc::exercise<2021, 16, 2>(aoc::res::data_2021_16)));
}
