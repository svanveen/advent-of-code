#ifndef ADVENT_OF_CODE_2020_EXERCISE06_H
#define ADVENT_OF_CODE_2020_EXERCISE06_H

#include <array>
#include <fstream>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace event2020::exercise6
{

namespace impl
{

template <typename FILTER>
auto exercise(std::istream& stream, FILTER&& filter)
{
    auto lines =  ranges::getlines(stream) | ranges::to_vector;

    auto answers = lines
        | ranges::views::split_when([](auto&& line) { return line.empty(); })
        | ranges::views::transform([filter](auto&& passengers)
            {
                return ranges::views::iota('a', 'z' + 1)
                    | ranges::views::filter([filter, passengers](auto&& q)
                        {
                            return filter(passengers, [q](auto&& str) { return str.find(q) != std::string::npos; });
                        });
            })
        | ranges::views::transform(ranges::distance);

    return ranges::accumulate(answers, std::size_t{0});
}

}

std::size_t part1(std::istream& stream)
{
    return impl::exercise(stream, ranges::any_of);
}

std::size_t part2(std::istream& stream)
{
    return impl::exercise(stream, ranges::all_of);
}

}


#endif //ADVENT_OF_CODE_2020_EXERCISE06_H
