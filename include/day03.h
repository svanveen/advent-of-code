#ifndef ADVENT_OF_CODE_DAY03_H
#define ADVENT_OF_CODE_DAY03_H

#include <array>
#include <fstream>
#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace day3
{

namespace impl
{

struct Slope
{
    std::size_t x;
    std::size_t y;
};

auto exercise(const std::string& path, std::initializer_list<Slope> slopes)
{
    std::ifstream stream{path};
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

auto exercise1(const std::string& path)
{
    return impl::exercise(path, {{3, 1}});
}

auto exercise2(const std::string& path)
{
    return impl::exercise(path, {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}});
}

}


#endif //ADVENT_OF_CODE_DAY03_H
