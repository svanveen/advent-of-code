#ifndef ADVENTOFCODE_EXERCISES_H
#define ADVENTOFCODE_EXERCISES_H

#include <iostream>
#include <aoc/exercises.h>

namespace aoc
{

template <std::size_t YEAR, std::size_t EXERCISE, std::size_t PART>
std::size_t exercise(std::istream& line);

}
#endif //ADVENTOFCODE_EXERCISES_H
