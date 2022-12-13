#ifndef ADVENTOFCODE_EXERCISE_H
#define ADVENTOFCODE_EXERCISE_H

#include <iostream>
#include <sstream>
#include <string_view>
#include <aoc/Result.h>

using namespace std::literals;

namespace aoc
{

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
Result exercise(std::istream& line);

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
Result exercise(std::string_view str)
{
    auto os = std::stringstream{};
    os << str;
    return exercise<YEAR, EXERCISE, PART>(os);
}

}
#endif //ADVENTOFCODE_EXERCISE_H
