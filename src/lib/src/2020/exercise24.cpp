#include <list>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position  = utils::Position<int, 2>;
using Direction = utils::Direction<int, 2>;

auto getDirection(const std::string& str)
{
    static const std::map<std::string, Direction> directionMap
    {
        {"e",  Direction{{+2,  0}}},
        {"w",  Direction{{-2,  0}}},
        {"ne", Direction{{+1, +1}}},
        {"nw", Direction{{-1, +1}}},
        {"se", Direction{{+1, -1}}},
        {"sw", Direction{{-1, -1}}},
    };
    return directionMap.at(str);
}

auto computePosition(const std::string& str)
{
    return ranges::accumulate(
        str | ranges::views::tokenize(std::regex{"[ns]?[ew]"}) | ranges::views::transform(getDirection),
        Position{}
    );
}

}

template <>
std::size_t exercise<2020, 24, 1>(std::istream& stream)
{
    auto tiles = ranges::getlines(stream)
        | ranges::views::transform(computePosition)
        | ranges::to_vector
        | ranges::actions::sort;

    auto blackTiles = tiles
        | ranges::views::unique
        | ranges::views::filter([&](auto&& tile) { return ranges::count(tiles, tile) % 2 == 1; });

    return ranges::distance(blackTiles);
}

template <>
std::size_t exercise<2020, 24, 2>(std::istream& stream)
{
    return 0;
}

}
