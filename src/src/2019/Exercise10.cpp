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
    return 0;
}

}
