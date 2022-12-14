#include <fstream>
#include <iostream>
#include <docopt/docopt.h>
#include <aoc/AllExercises.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH -y YEAR -e EXERCISE

Options:
  -p PATH       base path to directory containing all input .dat files per year
  -y YEAR       year of the event
  -e EXERCISE   exercise to execute
)";

template <typename CALLBACK>
auto solve(CALLBACK&& callback, const std::string& path)
{
    std::ifstream stream{path};
    return callback(stream);
}

void solveExercises(int year, int exercise, const std::string& basePath)
{
    const auto path = basePath + "/" + std::to_string(year) + "/" + std::to_string(exercise) + ".dat";
    const auto&[part1, part2] = aoc::exercises.at(year * 100 + exercise);

    std::cout << "Solutions for event " << year << " exercise " << exercise << std::endl;
    std::cout << "Part 1: " << solve(part1, path) << std::endl;
    std::cout << "Part 2: " << solve(part2, path) << std::endl;
}

int main(int argc, char** argv)
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc});

    const auto& year = args["-y"].asLong();
    const auto& exercise = args["-e"].asLong();
    const auto basePath = args["-p"].asString();

    try
    {
        solveExercises(year, exercise, basePath);
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "No solution for this exercise" << std::endl;
    }

    return 0;
}