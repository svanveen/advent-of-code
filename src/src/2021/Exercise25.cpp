#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

template <>
Result exercise<2021, 25, 1>(std::istream& stream)
{
    auto map = ranges::getlines(stream) | ranges::to_vector;
    const auto rows = map.size();
    const auto cols = map.front().size();

    for (const auto round : ranges::views::ints(1))
    {
        auto moved = false;
        auto copy = map;
        for (const auto row : ranges::views::indices(rows))
        {
            for (const auto col : ranges::views::indices(cols))
            {
                const auto next = (col + 1) % cols;
                if (map[row][col] == '>' && map[row][next] == '.')
                {
                    std::swap(copy[row][col], copy[row][next]);
                    moved = true;
                }
            }
        }
        map = copy;
        for (const auto row : ranges::views::indices(rows))
        {
            for (const auto col : ranges::views::indices(cols))
            {
                const auto next = (row + 1) % rows;
                if (map[row][col] == 'v' && map[next][col] == '.')
                {
                    std::swap(copy[row][col], copy[next][col]);
                    moved = true;
                }
            }
        }
        if (!moved)
        {
            return round;
        }
        map = std::move(copy);
    }
}

template <>
Result exercise<2021, 25, 2>(std::istream& stream)
{
    return 0;
}

}
