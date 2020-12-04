#include <iostream>
#include <docopt/docopt.h>
#include <aoc/day01.h>
#include <aoc/day02.h>
#include <aoc/day03.h>
#include <aoc/day04.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH [-d DAY]

Options:
  -p PATH  path to .dat files
  -d DAY   day to execute [default: 4]
)";

template <typename CALLBACK>
auto solve(CALLBACK&& callback, const std::string& path)
{
    std::ifstream stream{path};
    return callback(stream);
}

int main(int argc, char** argv)
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc});

    const auto& day = args["-d"].asLong();
    const auto path = args["-p"].asString() + "/" + std::to_string(day) + ".dat";

    std::cout << "Solutions day " << day << std::endl;
    switch (day)
    {
        case 1:
            std::cout << "Exercise 1: " << solve(day1::exercise1, path) << std::endl;
            std::cout << "Exercise 2: " << solve(day1::exercise2, path) << std::endl;
            break;
        case 2:
            std::cout << "Exercise 1: " << solve(day2::exercise1, path) << std::endl;
            std::cout << "Exercise 2: " << solve(day2::exercise2, path) << std::endl;
            break;
        case 3:
            std::cout << "Exercise 1: " << solve(day3::exercise1, path) << std::endl;
            std::cout << "Exercise 2: " << solve(day3::exercise2, path) << std::endl;
            break;
        case 4:
            std::cout << "Exercise 1: " << solve(day4::exercise1, path) << std::endl;
            std::cout << "Exercise 2: " << solve(day4::exercise2, path) << std::endl;
            break;
        default:
            std::cerr << "No solution for this day" << std::endl;
            return 1;
    }

    return 0;
}