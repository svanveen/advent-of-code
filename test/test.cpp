#include <gtest/gtest.h>
#include <sstream>
#include <aoc/day01.h>
#include <aoc/day02.h>
#include <aoc/day03.h>
#include <aoc/day04.h>

template <typename EXERCISE>
auto solve(EXERCISE&& exercise, const std::string& input)
{
    std::stringstream stream{input};
    return exercise(stream);
}

TEST(AdventOfCode, Day1)
{
    constexpr auto input = R"(
1721
979
366
299
675
1456
)";

    // exercise 1
    EXPECT_EQ(514579, solve(day1::exercise1, input));

    // exercise 2
    EXPECT_EQ(241861950, solve(day1::exercise2, input));
}

TEST(AdventOfCode, Day2)
{
    constexpr auto input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)";

    // exercise 1
    EXPECT_EQ(2, solve(day2::exercise1, input));

    // exercise 2
    EXPECT_EQ(1, solve(day2::exercise2, input));
}

TEST(AdventOfCode, Day3)
{
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

    // exercise 1
    EXPECT_EQ(7, solve(day3::exercise1, input));

    // exercise 2
    EXPECT_EQ(336, solve(day3::exercise2, input));
}

TEST(AdventOfCode, Day4)
{
    // exercise 1
    {
        constexpr auto input = R"(ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in
)";
        EXPECT_EQ(2, solve(day4::exercise1, input));
    }

    // exercise 2
    {
        constexpr auto input1 = R"(eyr:1972 cid:100
hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926

iyr:2019
hcl:#602927 eyr:1967 hgt:170cm
ecl:grn pid:012533040 byr:1946

hcl:dab227 iyr:2012
ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277

hgt:59cm ecl:zzz
eyr:2038 hcl:74454a iyr:2023
pid:3556412378 byr:2007
)";
        EXPECT_EQ(0, solve(day4::exercise2, input1));

        constexpr auto input2 = R"(pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
hcl:#623a2f

eyr:2029 ecl:blu cid:129 byr:1989
iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm

hcl:#888785
hgt:164cm byr:2001 iyr:2015 cid:88
pid:545766238 ecl:hzl
eyr:2022

iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719
)";
        EXPECT_EQ(4, solve(day4::exercise2, input2));
    }
}
