#ifndef ADVENTOFCODE_TOINT_H
#define ADVENTOFCODE_TOINT_H

#include <string>
#include <range/v3/view/transform.hpp>

namespace aoc::utils
{
    
inline auto toInts = ranges::views::transform([](const std::string& str)
{
    return std::stoi(str);
});
    
}

#endif // ADVENTOFCODE_TOINT_H
