#include <set>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<int, 2>;
using Direction = utils::Direction<int, 2>;

Direction reduce(const Direction& dir)
{
    const auto gcd = std::gcd(dir[0], dir[1]);
    return {{dir[0] / gcd, dir[1] / gcd}};
}

struct Asteriod
{
    Asteriod(int col, int row)
        : position({col, row})
    {}

    Position position;
    std::size_t count = 0;
};

auto findAsteroids(std::istream& stream)
{
    auto asteroids = std::vector<Asteriod>{};

    auto row = int{};
    for(const auto& line : ranges::getlines(stream))
    {
        auto col = int{};
        for (const auto entry : line)
        {
            if (entry == '#')
            {
                auto asteroid = Asteriod{col, row};

                constexpr auto directionLess = [](const Direction& lhs, const Direction& rhs)
                {
                    return lhs[0] * rhs[1] < rhs[0] * lhs[1];
                };
                auto directions = std::set<Direction, decltype(directionLess)>{directionLess};
                for (auto it = asteroids.rbegin(); it != asteroids.rend(); ++it)
                {
                    const auto direction = it->position - asteroid.position;
                    const auto [_, success] = directions.emplace(direction);
                    if (success)
                    {
                        ++asteroid.count;
                        ++it->count;
                    }
                }
                asteroids.emplace_back(asteroid);
            }
            ++col;
        }
        ++row;
    }
    return asteroids;
}

}

template <>
Result exercise<2019, 10, 1>(std::istream& stream)
{
    const auto asteroids = findAsteroids(stream);
    return ranges::max(asteroids | ranges::views::transform([](const auto& el) { return el.count; }));
}

template <>
Result exercise<2019, 10, 2>(std::istream& stream)
{
    const auto asteroids = findAsteroids(stream);

    constexpr auto lessCount = [](const auto& lhs, const auto& rhs)
    {
        return lhs.count < rhs.count;
    };
    const auto& laserPosition = ranges::max(asteroids, lessCount).position;

    auto asteroidPositions = std::set<Position>{};
    for (const auto& asteroid : asteroids)
    {
        asteroidPositions.emplace(asteroid.position);
    }

    const auto maxCol = ranges::max(asteroids | ranges::views::transform([](const auto& asteroid) { return asteroid.position[0]; }));
    const auto maxRow = ranges::max(asteroids | ranges::views::transform([](const auto& asteroid) { return asteroid.position[1]; }));

    auto count = 0;
    const auto border = ranges::views::zip
    (
        ranges::views::concat
        (
            ranges::views::closed_iota(laserPosition[0], maxCol),
            ranges::views::repeat_n(maxCol, maxRow - 1),
            ranges::views::closed_iota(0, maxCol) | ranges::views::reverse,
            ranges::views::repeat_n(0, maxRow - 1),
            ranges::views::iota(0, laserPosition[0])
        ),
        ranges::views::concat
        (
            ranges::views::repeat_n(0, maxCol - laserPosition[0]),
            ranges::views::closed_iota(0, maxRow),
            ranges::views::repeat_n(maxRow, maxCol - 1),
            ranges::views::closed_iota(0, maxRow) | ranges::views::reverse,
            ranges::views::repeat_n(0, laserPosition[0] - 1)
        )
    ) | ranges::views::transform([](const auto& coord) { return Position{{std::get<0>(coord), std::get<1>(coord)}}; });
    for (const auto& pos : border)
    {
        const auto direction = pos - laserPosition;
        auto reducedDirection = reduce(direction);
        for (auto dir = reducedDirection; dir != direction + reducedDirection; dir += reducedDirection)
        {
            auto it = std::find(asteroidPositions.begin(), asteroidPositions.end(), laserPosition + dir);
            if (it != asteroidPositions.end())
            {
                std::cout << *it << std::endl;
                asteroidPositions.erase(it);
                ++count;
                break;
            }
        }
    }

    return 0;
}

}
