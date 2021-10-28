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
    using Part = aoc::Result (&)(std::istream&);
    Part part1;
    Part part2;
};

#define EXERCISE(YEAR, EXERCISE)          \
  {                                       \
    YEAR##EXERCISE,                       \
    {                                     \
      aoc::exercise<YEAR, EXERCISE, 1>,   \
      aoc::exercise<YEAR, EXERCISE, 2>,   \
    }                                     \
  }
static const std::map<int, Exercise> exercises {
    EXERCISE(2020, 1),
    EXERCISE(2020, 2),
    EXERCISE(2020, 3),
    EXERCISE(2020, 4),
    EXERCISE(2020, 5),
    EXERCISE(2020, 6),
    EXERCISE(2020, 7),
    EXERCISE(2020, 8),
    EXERCISE(2020, 9),
    EXERCISE(2020, 10),
    EXERCISE(2020, 11),
    EXERCISE(2020, 12),
    EXERCISE(2020, 13),
    EXERCISE(2020, 14),
    EXERCISE(2020, 15),
    EXERCISE(2020, 16),
    EXERCISE(2020, 17),
    EXERCISE(2020, 18),
    EXERCISE(2020, 19),
    EXERCISE(2020, 20),
    EXERCISE(2020, 21),
    EXERCISE(2020, 22),
    EXERCISE(2020, 23),
    EXERCISE(2020, 24),
    EXERCISE(2020, 25),
};
#undef EXERCISE

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