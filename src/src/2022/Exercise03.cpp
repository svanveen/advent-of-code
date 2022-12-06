#include <bitset>
#include <bit>
#include <stdexcept>
#include <string_view>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

using Prio = std::size_t;

Prio char2Prio(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 1 + 26;
    }
    throw std::logic_error{"invalid char"};
}

template <typename RANGE>
Prio commonElement(RANGE&& itemLists)
{
    auto commonBits = std::bitset<52>{}.set();
    for (const auto& items : itemLists)
    {
        auto bits = std::bitset<52>{};
        for (const auto c : items)
        {
            bits.set(char2Prio(c) - 1);
        }
        commonBits &= bits;
        if (commonBits.count() == 1)
        {
            return std::bit_width(commonBits.to_ullong());
        }
    }
    throw std::logic_error{"no common element"};
}

}

template <>
Result exercise<2022, 3, 1>(std::istream& stream)
{
    auto prios = ranges::getlines(stream)
        | ranges::views::transform([](const auto& str)
            {
                const auto common = commonElement(std::vector
                {
                     std::string_view{str}.substr(0, str.size() / 2),
                     std::string_view{str}.substr(str.size() / 2)
                });
                return common;
            });
    return ranges::accumulate(prios, 0);
}

template <>
Result exercise<2022, 3, 2>(std::istream& stream)
{
    auto prios = ranges::getlines(stream)
        | ranges::views::chunk(3)
        | ranges::views::transform([](const auto& rng) { return commonElement(rng); });
    return ranges::accumulate(prios, 0);
}

}
