#ifndef ADVENTOFCODE_TOINT_H
#define ADVENTOFCODE_TOINT_H

#include <string>
#include <range/v3/view/transform.hpp>

namespace aoc::utils
{
    
template <typename INT>
inline auto toInts = ranges::views::transform([](const std::string& str)
{
    if constexpr (std::is_same_v<INT, int>)
    {
        return std::stoi(str);
    }
    else if constexpr (std::is_same_v<INT, long>)
    {
        return std::stol(str);
    }
    else if constexpr (std::is_same_v<INT, long long>)
    {
        return std::stoll(str);
    }
    else if constexpr (std::is_same_v<INT, unsigned long>)
    {
        return std::stoul(str);
    }
    else if constexpr (std::is_same_v<INT, unsigned long long>)
    {
        return std::stoull(str);
    }
    else
    {
        static_assert(!std::is_same_v<INT, INT>, "integer type not supported");
    }
});
    
}

#endif // ADVENTOFCODE_TOINT_H
