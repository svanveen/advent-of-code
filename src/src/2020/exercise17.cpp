#include <regex>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/CartesianProduct.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

template <std::size_t DIMS>
using ConwayCube = utils::Position<int, DIMS>;

template <std::size_t DIMS>
using Direction = utils::Direction<int, DIMS>;

template <std::size_t DIMS>
auto getNeighbors(const ConwayCube<DIMS>& cube)
{
    const auto rng = ranges::views::closed_iota(-1, 1);
    static const auto directions = utils::cartesian_product<DIMS>(rng)
        | ranges::views::transform([](auto&& tuple) { return Direction<DIMS>::create(tuple); });

    return directions
      | ranges::views::filter(ranges::bind_back(ranges::not_equal_to{}, Direction<DIMS>{}))
      | ranges::views::transform([&](auto&& dir) { return cube + dir; });
}


enum State
{
    ACTIVE = '#',
    INACTIVE = '.'
};

template <std::size_t DIMS>
std::size_t exercise(std::istream& stream)
{
    const auto initialState = ranges::getlines(stream)
        | ranges::to_vector;

    auto activeCubesRng = ranges::views::cartesian_product
    (
        ranges::views::indices(0, static_cast<int>(initialState.size())),
        ranges::views::indices(0, static_cast<int>(initialState[0].size()))
    ) | ranges::views::filter([&](auto&& tuple) { return initialState[std::get<0>(tuple)][std::get<1>(tuple)] == State::ACTIVE; })
      | ranges::views::transform([](auto&& tuple) { return std::pair{ConwayCube<DIMS>::create(tuple), true}; });

    auto activeCubes = std::map<ConwayCube<DIMS>, bool>{activeCubesRng.begin(), activeCubesRng.end()};

    auto getActiveNeighbours = [&](auto&& cube)
    {
        return getNeighbors(cube) | ranges::views::filter([&](auto&& neighbour) { return activeCubes[neighbour]; });
    };

    auto futureActive = [&](auto&& cube)
    {
        auto activeNeighbourCount = ranges::distance(getActiveNeighbours(cube));
        if (activeCubes[cube])
        {
            return activeNeighbourCount == 2 || activeNeighbourCount == 3;
        }
        else
        {
            return activeNeighbourCount == 3;
        }
    };

    for (int i = 0; i < 6; ++i)
    {
        auto candidates = activeCubes
            | ranges::views::keys
            | ranges::views::transform([](auto&& cube)
                {
                    return ranges::views::concat(ranges::views::single(cube), getNeighbors(cube));
                })
            | ranges::views::join
            | ranges::to_vector
            | ranges::actions::sort([](auto&& lhs, auto&& rhs) { return lhs < rhs; })
            | ranges::actions::unique;

        auto activeCubesRng = candidates
            | ranges::views::filter(futureActive)
            | ranges::views::transform([](auto&& cube) { return std::pair{cube, true}; });

        activeCubes = {activeCubesRng.begin(), activeCubesRng.end()};
    }

    return activeCubes.size();
}

}


template <>
Result exercise<2020, 17, 1>(std::istream& stream)
{
    return exercise<3>(stream);
}

template <>
Result exercise<2020, 17, 2>(std::istream& stream)
{
    return exercise<4>(stream);
}

}
