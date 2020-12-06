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

auto exercise(std::istream& stream)
{
    auto lines =  ranges::getlines(stream) | ranges::to_vector;

    auto answers = lines
        | ranges::views::split_when([](auto&& line) { return line.empty(); })
        | ranges::views::transform(ranges::bind_back(ranges::accumulate, std::string{}, std::plus{}))
        | ranges::views::transform(ranges::actions::sort)
        | ranges::views::transform(ranges::actions::unique)
        | ranges::views::transform(ranges::distance);

    return ranges::accumulate(answers, std::size_t{0});
}

}

std::size_t part1(std::istream& stream)
{
    return impl::exercise(stream);
}

std::size_t part2(std::istream& stream)
{
    return 0;
}

}


#endif //ADVENT_OF_CODE_2020_EXERCISE06_H
