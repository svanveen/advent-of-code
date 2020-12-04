#include <iostream>
#include <docopt/docopt.h>
#include <aoc/exercise01.h>
#include <aoc/exercise02.h>
#include <aoc/exercise03.h>
#include <aoc/exercise04.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH [-e EXERCISE]

Options:
  -p PATH       path to .dat files
  -e EXERCISE   exercise to execute [default: 4]
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

    const auto& exercise = args["-e"].asLong();
    const auto path = args["-p"].asString() + "/" + std::to_string(exercise) + ".dat";

    std::cout << "Solutions for exercise " << exercise << std::endl;
    switch (exercise)
    {
        case 1:
            std::cout << "Part 1: " << solve(exercise1::part1, path) << std::endl;
            std::cout << "Part 2: " << solve(exercise1::part2, path) << std::endl;
            break;
        case 2:
            std::cout << "Part 1: " << solve(exercise2::part1, path) << std::endl;
            std::cout << "Part 2: " << solve(exercise2::part2, path) << std::endl;
            break;
        case 3:
            std::cout << "Part 1: " << solve(exercise3::part1, path) << std::endl;
            std::cout << "Part 2: " << solve(exercise3::part2, path) << std::endl;
            break;
        case 4:
            std::cout << "Part 1: " << solve(exercise4::part1, path) << std::endl;
            std::cout << "Part 2: " << solve(exercise4::part2, path) << std::endl;
            break;
        default:
            std::cerr << "No solution for this exercise" << std::endl;
            return 1;
    }

    return 0;
}