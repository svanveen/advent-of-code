#ifndef ADVENT_OF_CODE_EXERCISE05_H
#define ADVENT_OF_CODE_EXERCISE05_H

#include <array>
#include <fstream>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace event2020::exercise5
{

namespace impl
{

auto toBit(char c)
{
    return (c == 'B') || (c == 'R');
}

auto parseSeatNumber(const std::string& str)
{
    return ranges::accumulate(str | ranges::views::transform(toBit), 0, [](auto&& lhs, auto&& rhs)
    {
        return lhs * 2 + rhs;
    });
}

auto exercise(std::istream& stream)
{
    return ranges::getlines(stream)
            | ranges::views::transform(parseSeatNumber);
}

}

std::size_t part1(std::istream& stream)
{
    return ranges::max(impl::exercise(stream));
}

std::size_t part2(std::istream& stream)
{
    auto ids = impl::exercise(stream)
        | ranges::to_vector
        | ranges::actions::sort
        | ranges::actions::adjacent_remove_if([](auto&& lhs, auto&& rhs) { return lhs + 1 == rhs; });

    return ranges::front(ids) + 1;
}

}


#endif //ADVENT_OF_CODE_EXERCISE05_H
