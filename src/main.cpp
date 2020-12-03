#include <iostream>
#include <docopt/docopt.h>
#include <day01.h>
#include <day02.h>
#include <day03.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH -d DAY

Options:
  -p PATH  path to .dat files
  -d DAY   day to execute
)";

int main(int argc, char** argv)
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc});

    const auto& path = args["-p"].asString();
    const auto& day = args["-d"].asLong();

    std::cout << "Solutions day " << day << std::endl;
    switch (day)
    {
        case 1:
            std::cout << "Exercise 1: " << day1::exercise1(path) << std::endl;
            std::cout << "Exercise 2: " << day1::exercise2(path) << std::endl;
            break;
        case 2:
            std::cout << "Exercise 1: " << day2::exercise1(path) << std::endl;
            std::cout << "Exercise 2: " << day2::exercise2(path) << std::endl;
            break;
        case 3:
            std::cout << "Exercise 1: " << day3::exercise1(path) << std::endl;
            std::cout << "Exercise 2: " << day3::exercise2(path) << std::endl;
            break;
        default:
            std::cerr << "No solution for this day" << std::endl;
            return 1;
    }

    return 0;
}