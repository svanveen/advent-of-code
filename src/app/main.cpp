#include <iostream>
#include <docopt/docopt.h>
#include <aoc/2020/exercise01.h>
#include <aoc/2020/exercise02.h>
#include <aoc/2020/exercise03.h>
#include <aoc/2020/exercise04.h>
#include <aoc/2020/exercise05.h>
#include <aoc/2020/exercise06.h>
#include <aoc/2020/exercise07.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH [-y YEAR] [-e EXERCISE]

Options:
  -p PATH       path to .dat files
  -y YEAR       year of the event [default: 2020]
  -e EXERCISE   exercise to execute [default: 7]
)";

struct Exercise
{
    using Part = std::size_t (&)(std::istream&);
    Part part1;
    Part part2;
};

static const std::map<int, Exercise> exercises {
    {202001, {event2020::exercise1::part1, event2020::exercise1::part2}},
    {202002, {event2020::exercise2::part1, event2020::exercise2::part2}},
    {202003, {event2020::exercise3::part1, event2020::exercise3::part2}},
    {202004, {event2020::exercise4::part1, event2020::exercise4::part2}},
    {202005, {event2020::exercise5::part1, event2020::exercise5::part2}},
    {202006, {event2020::exercise6::part1, event2020::exercise6::part2}},
    {202007, {event2020::exercise7::part1, event2020::exercise7::part2}},
};

template <typename CALLBACK>
auto solve(CALLBACK&& callback, const std::string& path)
{
    std::ifstream stream{path};
    return callback(stream);
}

void solveExercises(int year, int exercise, const std::string& basePath)
{
    const auto path = basePath + "/" + std::to_string(year) + "/" + std::to_string(exercise) + ".dat";
    const auto&[part1, part2] = exercises.at(year * 100 + exercise);
    std::ifstream stream{path};

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
    catch(...)
    {
        std::cerr << "No solution for this exercise" << std::endl;
    }

    return 0;
}