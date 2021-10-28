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

enum class Color
{
    WHITE,
    BLACK,
};

using Position  = utils::Position<int, 2>;
using Direction = utils::Direction<int, 2>;

static const std::map<std::string, Direction> directionMap
{
    {"e",  Direction{{+2,  0}}},
    {"w",  Direction{{-2,  0}}},
    {"ne", Direction{{+1, +1}}},
    {"nw", Direction{{-1, +1}}},
    {"se", Direction{{+1, -1}}},
    {"sw", Direction{{-1, -1}}},
};

auto getDirection(const std::string& str)
{
    return directionMap.at(str);
}

auto getNeighbors(const Position& position)
{
    return directionMap
        | ranges::views::values
        | ranges::views::transform([=](auto&& direction) { return position + direction; });
}

auto computePosition(const std::string& str)
{
    return ranges::accumulate(
        str | ranges::views::tokenize(std::regex{"[ns]?[ew]"}) | ranges::views::transform(getDirection),
        Position{}
    );
}

auto getBlackTiles(std::istream& stream)
{
    auto tiles = ranges::getlines(stream)
        | ranges::views::transform(computePosition)
        | ranges::to_vector
        | ranges::actions::sort;

    return tiles
        | ranges::views::unique
        | ranges::views::filter([&](auto&& tile) { return ranges::count(tiles, tile) % 2 == 1; })
        | ranges::to_vector;
}

}

template <>
Result exercise<2020, 24, 1>(std::istream& stream)
{
    const auto blackTiles = getBlackTiles(stream);

    return blackTiles.size();
}

template <>
Result exercise<2020, 24, 2>(std::istream& stream)
{
    auto blackTiles = getBlackTiles(stream); // TODO: why can't the statements be combined using actions::transform

    auto tilesMapRng = blackTiles
        | ranges::views::transform([](auto&& tile) { return std::pair{tile, Color::BLACK}; });

    auto tilesMap = std::map<Position, Color>{tilesMapRng.begin(), tilesMapRng.end()};
    auto shouldFlip = [&](auto&& tile)
    {
        const auto blackNeighborsCount = ranges::distance(
            getNeighbors(tile)
                | ranges::views::filter([&](auto&& neighbor) { return tilesMap[neighbor] == Color::BLACK; })
        );
        return ((tilesMap[tile] == Color::BLACK) && (blackNeighborsCount == 0 || blackNeighborsCount > 2)) ||
                (tilesMap[tile] == Color::WHITE && (blackNeighborsCount == 2));
    };
    auto isBlack = [](auto&& tileColorPair)
    {
        return tileColorPair.second == Color::BLACK;
    };
    for (int day = 1; day <= 100; ++day)
    {
        const auto tilesToFlip = tilesMap
            | ranges::views::filter(isBlack)
            | ranges::views::keys
            | ranges::views::transform([](auto&& tile) { return ranges::views::concat(ranges::views::single(tile), getNeighbors(tile)); })
            | ranges::views::join
            | ranges::to_vector
            | ranges::actions::sort
            | ranges::actions::unique
            | ranges::actions::remove_if(ranges::not_fn(shouldFlip));

        for (auto&& tile : tilesToFlip)
        {
            auto& color = tilesMap[tile];
            color = (color == Color::BLACK) ? Color::WHITE : Color::BLACK;
        }
    }
    return ranges::distance(tilesMap | ranges::views::filter(isBlack));
}

}
