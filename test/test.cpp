#include <gtest/gtest.h>
#include <sstream>
#include <aoc/day01.h>
#include <aoc/day02.h>
#include <aoc/day03.h>

template <typename EXERCISE, typename EXPECTATION>
void testSolution(EXERCISE&& exercise, const std::string& input, EXPECTATION&& expectation)
{
    std::stringstream stream{input};
    EXPECT_EQ(expectation, exercise(stream));
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
    testSolution(day1::exercise1, input, 514579);

    // exercise 2
    testSolution(day1::exercise2, input, 241861950);
}

TEST(AdventOfCode, Day2)
{
    constexpr auto input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)";

    // exercise 1
    testSolution(day2::exercise1, input, 2);

    // exercise 2
    testSolution(day2::exercise2, input, 1);
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
    testSolution(day3::exercise1, input, 7);

    // exercise 2
    testSolution(day3::exercise2, input, 336);
}
