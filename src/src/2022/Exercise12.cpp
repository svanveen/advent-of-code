#include <optional>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<int, 2>;
using Direction = utils::Direction<int, 2>;

struct Grid
{
    struct Field
    {
        int elevation;
        std::optional<std::size_t> shortestDistance;
    };

    Field& operator[](const Position& pos)
    {
        return fields[pos[0]][pos[1]];
    }

    bool isValid(const Position& pos) const
    {
        return pos[0] >= 0 && pos[0] < fields.size() && pos[1] >= 0 && pos[1] < fields.front().size();
    }

    std::vector<std::vector<Field>> fields;
    std::vector<Position> possibleStarts;
    Position start;
    Position end;
};

Grid parseGrid(std::istream& stream)
{
    auto possibleStarts = std::vector<Position>{};
    auto start = Position{};
    auto end = Position{};
    auto elevations = ranges::getlines(stream)
        | ranges::views::enumerate
        | ranges::views::transform([&](const auto& pair)
            {
                const auto row = static_cast<int>(pair.first);
                return pair.second
                    | ranges::views::enumerate
                    | ranges::views::transform([&possibleStarts, &start, &end, row](const auto& pair) -> Grid::Field
                        {
                            const auto col = static_cast<int>(pair.first);
                            if (pair.second == 'S')
                            {
                                start = Position{{row, col}};
                                return {0};
                            }
                            if (pair.second == 'E')
                            {
                                end = Position{{row, col}};
                                return {25};
                            }
                            if (pair.second == 'a' || pair.second == 'S')
                            {
                                possibleStarts.push_back(Position{{row, col}});
                            }
                            return {pair.second - 'a'};
                        })
                    | ranges::to_vector;
            })
        | ranges::to_vector;

    return Grid{elevations, possibleStarts, start, end};
}

void computeShortestPaths(Grid& grid, const Position& pos, int distance = 0)
{
    constexpr auto directions = std::array
    {
        Direction{{ 1,  0}},
        Direction{{-1,  0}},
        Direction{{ 0,  1}},
        Direction{{ 0, -1}}
    };
    auto& field = grid[pos];
    if (field.shortestDistance && *field.shortestDistance <= distance)
    {
        return;
    }
    field.shortestDistance = distance;
    
    if (pos == grid.start)
    {
        return;
    }

    for (const auto& dir : directions)
    {
        const auto nextPos = pos + dir;
        if (!grid.isValid(nextPos))
        {
            continue;
        }

        const auto& nextField = grid[nextPos];
        if (field.elevation - 1 <= nextField.elevation)
        {
            computeShortestPaths(grid, nextPos, distance + 1);
        }
    }
}

}

template <>
Result exercise<2022, 12, 1>(std::istream& stream)
{
    auto grid = parseGrid(stream);
    computeShortestPaths(grid, grid.end);
    return *grid[grid.start].shortestDistance;
}

template <>
Result exercise<2022, 12, 2>(std::istream& stream)
{
    auto grid = parseGrid(stream);
    computeShortestPaths(grid, grid.end);
    return ranges::min(grid.possibleStarts | ranges::views::transform([&](const auto& pos)
    {
        return grid[pos].shortestDistance.value_or(std::numeric_limits<std::size_t>::max());
    }));
}

}
