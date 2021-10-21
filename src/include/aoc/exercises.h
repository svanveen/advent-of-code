#ifndef ADVENTOFCODE_EXERCISES_H
#define ADVENTOFCODE_EXERCISES_H

#include <iostream>
#include <sstream>
#include <string_view>
#include <aoc/exercises.h>

namespace aoc
{

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
std::size_t exercise(std::istream& line);

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
std::size_t exercise(std::string_view str)
{
  auto os = std::stringstream{};
  os << str;
  return exercise<YEAR, EXERCISE, PART>(os);
}

}
#endif //ADVENTOFCODE_EXERCISES_H
