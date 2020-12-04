#ifndef ADVENT_OF_CODE_EXERCISE03_H
#define ADVENT_OF_CODE_EXERCISE03_H

#include <array>
#include <fstream>
#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace exercise3
{

namespace impl
{

struct Slope
{
    std::size_t x;
    std::size_t y;
};

auto exercise(std::istream& stream, std::initializer_list<Slope> slopes)
{
    auto forest = ranges::getlines(stream) | ranges::to_vector;

    auto solutions = slopes | ranges::views::transform([&](auto&& slope)
    {
        auto trees = ranges::views::iota(0u, (forest.size() - 1) / slope.y + 1)
                | ranges::views::filter([&](auto&& n) { return forest[n * slope.y][n * slope.x % forest[0].size()] == '#'; });
        return ranges::distance(trees);
    });

    return ranges::accumulate(solutions, std::size_t{1}, std::multiplies{});
}

}

auto part1(std::istream& stream)
{
    return impl::exercise(stream, {{3, 1}});
}

auto part2(std::istream& stream)
{
    return impl::exercise(stream, {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}});
}

}


#endif //ADVENT_OF_CODE_EXERCISE03_H
