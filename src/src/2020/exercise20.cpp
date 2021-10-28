#include <regex>
#include <string>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct Tile
{
    auto getEdges() const
    {
        return std::array {
            data.front() | ranges::to_vector,
            data.back() | ranges::to_vector,
            ranges::views::indices(std::size_t{0}, data.size()) | ranges::views::transform([&](auto&& idx) { return data[idx].front(); }) | ranges::to_vector,
            ranges::views::indices(std::size_t{0}, data.size()) | ranges::views::transform([&](auto&& idx) { return data[idx].back(); }) | ranges::to_vector,
        };
    }

    bool hasMatchingEdge(const Tile& other)
    {
        if (id == other.id)
        {
            return false;
        }
        const auto edges = getEdges();
        const auto otherEdges = other.getEdges();
        return ranges::any_of(
            ranges::views::cartesian_product(edges, otherEdges),
            [](auto&& tuple)
            {
                const auto& [lhs, rhs] = tuple;
                return ranges::equal(lhs, rhs) || ranges::equal(lhs, rhs | ranges::views::reverse);
            }
        );
    }


    std::size_t id;
    std::vector<std::string> data;
};

template <typename Rng>
Tile parseTile(Rng&& rng)
{
    static const std::regex regex{R"(Tile (\d+):)"};
    std::smatch match;
    if (!std::regex_match(*rng.begin(), match, regex))
    {
        throw std::runtime_error{"parse error"};
    }

    return {std::stoull(match[1]), rng | ranges::views::drop(1) | ranges::to_vector};
}

}

template <>
Result exercise<2020, 20, 1>(std::istream& stream)
{
    auto tiles = ranges::getlines(stream)
        | ranges::views::split("")
        | ranges::views::transform([](auto&& tileRng) { return parseTile(tileRng); })
        | ranges::to_vector;

    auto isCornerTile = [&](auto&& tile)
    {
        auto hasMatchingEdge = [&](auto&& other)
        {
            return tile.hasMatchingEdge(other);
        };
        return ranges::distance(tiles | ranges::views::filter(hasMatchingEdge)) == 2;
    };

    auto cornerTileIds = tiles
        | ranges::views::filter(isCornerTile)
        | ranges::views::transform([](auto&& tile) { return tile.id; });

    return ranges::accumulate(cornerTileIds, std::size_t{1}, std::multiplies<>{});
}

template <>
Result exercise<2020, 20, 2>(std::istream& stream)
{
    return 0;
}

}
