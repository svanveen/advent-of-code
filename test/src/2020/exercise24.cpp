#include <gtest/gtest.h>
#include <aoc/exercises.h>
#include <aoc/res/2020/Data-24.h>

constexpr auto input = R"(sesenwnenenewseeswwswswwnenewsewsw
neeenesenwnwwswnenewnwwsewnenwseswesw
seswneswswsenwwnwse
nwnwneseeswswnenewneswwnewseswneseene
swweswneswnenwsewnwneneseenw
eesenwseswswnenwswnwnwsewwnwsene
sewnenenenesenwsewnenwwwse
wenwwweseeeweswwwnwwe
wsweesenenewnwwnwsenewsenwwsesesenwne
neeswseenwwswnwswswnw
nenwswwsewswnenenewsenwsenwnesesenew
enewnwewneswsewnwswenweswnenwsenwsw
sweneswneswneneenwnewenewwneswswnese
swwesenesewenwneswnwwneseswwne
enesenwswwswneneswsenwnewswseenwsese
wnwnesenesenenwwnenwsewesewsesesew
nenewswnwewswnenesenwnesewesw
eneswnwswnwsenenwnwnwwseeswneewsenese
neswnwewnwnwseenwseesewsenwsweewe
wseweeenwnesenwwwswnew
)";

TEST(Exercise24, Part1)
{
    EXPECT_EQ(10, (aoc::exercise<2020, 24, 1>(input)));
    EXPECT_EQ(521, (aoc::exercise<2020, 24, 1>(aoc::res::data_2020_24)));
}

TEST(Exercise24, Part2)
{
    EXPECT_EQ(2208, (aoc::exercise<2020, 24, 2>(input)));
    EXPECT_EQ(4242, (aoc::exercise<2020, 24, 2>(aoc::res::data_2020_24)));
}

