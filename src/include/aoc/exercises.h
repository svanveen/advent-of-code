#ifndef ADVENTOFCODE_EXERCISES_H
#define ADVENTOFCODE_EXERCISES_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string_view>
#include <aoc/Result.h>

namespace aoc
{

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
Result exercise(std::istream& line);

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
Result exercise(std::string_view str)
{
  auto stream = std::stringstream{};
  stream << str;
  return exercise<YEAR, EXERCISE, PART>(stream);
}

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
Result exercise(const std::filesystem::path& path)
{
    auto stream = std::ifstream{path};
    return exercise<YEAR, EXERCISE, PART>(stream);
}

}
#endif //ADVENTOFCODE_EXERCISES_H
