#include <regex>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct ConwayCube
{
    constexpr ConwayCube(int x, int y, int z = 0)
        : x(x)
        , y(y)
        , z(z)
    {}

    static ConwayCube create(const std::tuple<int, int, int>& tuple)
    {
        return ConwayCube{std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)};
    }

    ConwayCube operator+(const ConwayCube& other) const { return {x + other.x, y + other.y, z + other.z}; }

    bool operator==(const ConwayCube& other) const { return (x == other.x) && (y == other.y) && (z == other.z); }
    bool operator!=(const ConwayCube& other) const { return !(*this == other); }
    bool operator<(const ConwayCube& other) const { return (x < other.x) || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z); }

    friend std::ostream& operator<<(std::ostream& stream, const ConwayCube& cube)
    {
        return stream << '[' << cube.x << ',' << cube.y << ',' << cube.z << ']';
    }

    int x;
    int y;
    int z;
};

static constexpr ConwayCube origin{0, 0, 0};

auto getNeighbors(const ConwayCube& cube)
{
    static const auto directions = ranges::views::cartesian_product
    (
        ranges::views::closed_iota(-1, 1),
        ranges::views::closed_iota(-1, 1),
        ranges::views::closed_iota(-1, 1)
    ) | ranges::views::transform(ConwayCube::create);

    return directions
      | ranges::views::filter(ranges::bind_back(ranges::not_equal_to{}, origin))
      | ranges::views::transform([&](auto&& dir) { return cube + dir; });
}


enum State
{
    ACTIVE = '#',
    INACTIVE = '.'
};

}

template <>
std::size_t exercise<2020, 17, 1>(std::istream& stream)
{
    const auto initialState = ranges::getlines(stream)
        | ranges::to_vector;

    auto activeCubesRng = ranges::views::cartesian_product
    (
        ranges::views::indices(0, static_cast<int>(initialState.size())),
        ranges::views::indices(0, static_cast<int>(initialState[0].size()))
    ) | ranges::views::filter([&](auto&& tuple) { return initialState[std::get<0>(tuple)][std::get<1>(tuple)] == State::ACTIVE; })
      | ranges::views::transform([](auto&& tuple) { return std::pair{ConwayCube{std::get<0>(tuple), std::get<1>(tuple), 0}, true}; });

    auto activeCubes = std::map<ConwayCube, bool>{activeCubesRng.begin(), activeCubesRng.end()};

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

        activeCubes = std::map<ConwayCube, bool>{activeCubesRng.begin(), activeCubesRng.end()};
    }

    return activeCubes.size();
}

template <>
std::size_t exercise<2020, 17, 2>(std::istream& stream)
{
    return 0;
}

}
