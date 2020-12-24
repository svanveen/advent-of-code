#include <fstream>
#include <istream>
#include <docopt/docopt.h>
#include <aoc/exercises.h>

constexpr auto USAGE = R"(Advent of Code.

Usage:
  advent-of-code -p PATH [-y YEAR] [-e EXERCISE]

Options:
  -p PATH       path to .dat files
  -y YEAR       year of the event
  -e EXERCISE   exercise to execute
)";

struct Exercise
{
    using Part = std::size_t (&)(std::istream&);
    Part part1;
    Part part2;
};

static const std::map<int, Exercise> exercises {
    {202001, {aoc::exercise<2020, 1, 1>, aoc::exercise<2020, 1, 2>}},
    {202002, {aoc::exercise<2020, 2, 1>, aoc::exercise<2020, 2, 2>}},
    {202003, {aoc::exercise<2020, 3, 1>, aoc::exercise<2020, 3, 2>}},
    {202004, {aoc::exercise<2020, 4, 1>, aoc::exercise<2020, 4, 2>}},
    {202005, {aoc::exercise<2020, 5, 1>, aoc::exercise<2020, 5, 2>}},
    {202006, {aoc::exercise<2020, 6, 1>, aoc::exercise<2020, 6, 2>}},
    {202007, {aoc::exercise<2020, 7, 1>, aoc::exercise<2020, 7, 2>}},
    {202008, {aoc::exercise<2020, 8, 1>, aoc::exercise<2020, 8, 2>}},
    {202009, {aoc::exercise<2020, 9, 1>, aoc::exercise<2020, 9, 2>}},
    {202010, {aoc::exercise<2020, 10, 1>, aoc::exercise<2020, 10, 2>}},
    {202011, {aoc::exercise<2020, 11, 1>, aoc::exercise<2020, 11, 2>}},
    {202012, {aoc::exercise<2020, 12, 1>, aoc::exercise<2020, 12, 2>}},
    {202013, {aoc::exercise<2020, 13, 1>, aoc::exercise<2020, 13, 2>}},
    {202014, {aoc::exercise<2020, 14, 1>, aoc::exercise<2020, 14, 2>}},
    {202015, {aoc::exercise<2020, 15, 1>, aoc::exercise<2020, 15, 2>}},
    {202016, {aoc::exercise<2020, 16, 1>, aoc::exercise<2020, 16, 2>}},
    {202017, {aoc::exercise<2020, 17, 1>, aoc::exercise<2020, 17, 2>}},
    {202018, {aoc::exercise<2020, 18, 1>, aoc::exercise<2020, 18, 2>}},
    {202019, {aoc::exercise<2020, 19, 1>, aoc::exercise<2020, 19, 2>}},
    {202020, {aoc::exercise<2020, 20, 1>, aoc::exercise<2020, 20, 2>}},
    {202021, {aoc::exercise<2020, 21, 1>, aoc::exercise<2020, 21, 2>}},
    {202022, {aoc::exercise<2020, 22, 1>, aoc::exercise<2020, 22, 2>}},
    {202023, {aoc::exercise<2020, 23, 1>, aoc::exercise<2020, 23, 2>}},
    {202024, {aoc::exercise<2020, 24, 1>, aoc::exercise<2020, 24, 2>}},
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