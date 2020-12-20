#include <Config.h>
#include <fstream>
#include <istream>
#include <docopt/docopt.h>
#include <aoc/exercises.h>

constexpr auto USAGE = R"(Current Exercise.

Usage:
  current-exercise -p PATH

Options:
  -p PATH  path to .dat files
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

    const auto basePath = args["-p"].asString();

    try
    {
        const auto path = basePath + "/" + std::to_string(YEAR) + "/" + std::to_string(EXERCISE) + ".dat";

        std::cout << "Solutions for event " << YEAR << " exercise " << EXERCISE << std::endl;
        std::cout << "Part 1: " << solve(aoc::exercise<YEAR, EXERCISE, 1>, path) << std::endl;
        std::cout << "Part 2: " << solve(aoc::exercise<YEAR, EXERCISE, 2>, path) << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}