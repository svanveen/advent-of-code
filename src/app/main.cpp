#include <iostream>
#include <docopt/docopt.h>
#include <aoc/exercise01.h>
#include <aoc/exercise02.h>
#include <aoc/exercise03.h>
#include <aoc/exercise04.h>
#include <aoc/exercise05.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH [-e EXERCISE]

Options:
  -p PATH       path to .dat files
  -e EXERCISE   exercise to execute [default: 5]
)";

struct Exercise
{
    using Part = std::size_t (&)(std::istream&);
    Part part1;
    Part part2;
};

static const std::map<int, Exercise> exercises {
    {1, {exercise1::part1, exercise1::part2}},
    {2, {exercise2::part1, exercise2::part2}},
    {3, {exercise3::part1, exercise3::part2}},
    {4, {exercise4::part1, exercise4::part2}},
    {5, {exercise5::part1, exercise5::part2}},
};

template <typename CALLBACK>
auto solve(CALLBACK&& callback, const std::string& path)
{
    std::ifstream stream{path};
    return callback(stream);
}

void solveExercises(int exercise, const std::string& basePath)
{
    const auto path = basePath + "/" + std::to_string(exercise) + ".dat";
    const auto&[part1, part2] = exercises.at(exercise);
    std::ifstream stream{path};

    std::cout << "Solutions for exercise " << exercise << std::endl;
    std::cout << "Part 1: " << solve(part1, path) << std::endl;
    std::cout << "Part 2: " << solve(part2, path) << std::endl;
}

int main(int argc, char** argv)
{
    auto args = docopt::docopt(USAGE, {argv + 1, argv + argc});

    const auto& exercise = args["-e"].asLong();
    const auto basePath = args["-p"].asString();

    try
    {
        solveExercises(exercise, basePath);
    }
    catch(...)
    {
        std::cerr << "No solution for this exercise" << std::endl;
    }

    return 0;
}