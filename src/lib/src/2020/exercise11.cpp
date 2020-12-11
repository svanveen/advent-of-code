#include <string>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <range/v3/algorithm.hpp>

namespace aoc
{

namespace
{

struct Map
{
    using Coord = std::tuple<int, int>;

    enum class Field : char
    {
        FLOOR    = '.',
        EMPTY    = 'L',
        OCCUPIED = '#'
    };

    static auto toField(char c)
    {
        return static_cast<Field>(c);
    }

    Map(std::istream& stream, int threshold, int neighborDist)
        : _map(ranges::getlines(stream) | ranges::views::transform([](auto&& line) { return line | ranges::views::transform(Map::toField) | ranges::to_vector; }) | ranges::to_vector)
        , _rows(_map.size())
        , _cols(_map[0].size())
        , _threshold(threshold)
        , _neighborDist(neighborDist)
    {}

    const Field& operator()(const Coord& coord) const
    {
        const auto& [x, y] = coord;
        return _map[x][y];
    }

    auto getCoordinates() const
    {
        return ranges::views::cartesian_product(ranges::views::iota(0, static_cast<int>(_rows)), ranges::views::iota(0, static_cast<int>(_cols)));
    }

    auto getNeighbors(const Coord& coord) const
    {
        static constexpr std::array<std::pair<int, int>, 8> directions =
        {{
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        }};
        return directions
            | ranges::views::transform([&](auto&& dir)
                {
                    return ranges::views::closed_iota(1, _neighborDist)
                        | ranges::views::transform([=](auto&& factor)
                            {
                                const auto&[x, y] = coord;
                                const auto&[dx, dy] = dir;
                                return std::pair{x + factor * dx, y + factor * dy};
                            })
                        | ranges::views::take_while([&](auto&& neighbor)
                            {
                                const auto&[x, y] = neighbor;
                                return (x >= 0 && x < _rows && y >= 0 && y < _cols);
                            })
                        | ranges::views::drop_while([&](auto&& neighbor)
                            {
                                const auto&[x, y] = neighbor;
                                return _map[x][y] == Field::FLOOR;
                            })
                        | ranges::views::take(1);
                })
            | ranges::views::join;
    }

    bool mustSwitch(const Coord& coord)
    {
        switch ((*this)(coord))
        {
            case Field::FLOOR:
                return false;
            case Field::EMPTY:
                return ranges::none_of(getNeighbors(coord) | ranges::views::transform(*this), ranges::bind_back(ranges::equal_to{}, Field::OCCUPIED));
            case Field::OCCUPIED:
                return ranges::distance(getNeighbors(coord) | ranges::views::transform(*this) | ranges::views::filter(ranges::bind_back(ranges::equal_to{}, Field::OCCUPIED))) >= _threshold;
        }
    }

    void switchField(const Coord& coord)
    {
        const auto& [x, y] = coord;
        switch (_map[x][y])
        {
            case Field::EMPTY:
                _map[x][y] = Field::OCCUPIED;
                break;
            case Field::OCCUPIED:
                _map[x][y] = Field::EMPTY;
                break;
            case Field::FLOOR:
                return;
        }
    }

    auto getSwitchableFields()
    {
        return getCoordinates()
            | ranges::views::filter([&](auto&& coord) { return mustSwitch(coord); })
            | ranges::to_vector;
    }

    auto getNumberOfOccupied() const
    {
        return ranges::distance(getCoordinates() | ranges::views::filter(ranges::bind_back(ranges::equal_to{}, Map::Field::OCCUPIED), *this));
    }

private:
    std::vector<std::vector<Field>> _map;
    std::size_t _rows;
    std::size_t _cols;
    int _threshold;
    int _neighborDist;
};

auto exercise(std::istream& stream, int threshold, int neighborDist)
{
    auto map = Map{stream, threshold, neighborDist};

    for (auto coordsToSwitch = map.getSwitchableFields(); !coordsToSwitch.empty(); coordsToSwitch = map.getSwitchableFields())
    {
        for (auto&& coord : coordsToSwitch)
        {
            map.switchField(coord);
        }
    }
    return map.getNumberOfOccupied();
}

}

template <>
std::size_t exercise<2020, 11, 1>(std::istream& stream)
{
    return exercise(stream, 4, 1);
}

template <>
std::size_t exercise<2020, 11, 2>(std::istream& stream)
{
    return exercise(stream, 5, std::numeric_limits<int>::max());
}

}
