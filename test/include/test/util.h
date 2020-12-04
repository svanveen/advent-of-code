#ifndef ADVENTOFCODE_UTIL_H
#define ADVENTOFCODE_UTIL_H

#include <sstream>
#include <string>

template <typename EXERCISE>
auto solve(EXERCISE&& exercise, const std::string& input)
{
    std::stringstream stream{input};
    return exercise(stream);
}

#endif //ADVENTOFCODE_UTIL_H
