#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

Result exercise(std::istream& stream, int days)
{
    auto population = ranges::getlines(stream, ',')
        | ranges::views::transform([](auto&& str) { return std::stoi(str); });

    auto countWithTimer = std::array<std::size_t, 9>{};
    for (const auto& p : population)
    {
        ++countWithTimer[p];
    }

    for (int day = 0; day < days; ++day)
    {
        auto newCounts = decltype(countWithTimer){};
        for (int timer = 1; timer < 9; ++timer)
        {
            newCounts[timer - 1] = countWithTimer[timer];
        }
        newCounts[6] += countWithTimer[0];
        newCounts[8] = countWithTimer[0];
        countWithTimer = newCounts;
    }
    return ranges::accumulate(countWithTimer, std::size_t{0});
}

}

template <>
Result exercise<2021, 6, 1>(std::istream& stream)
{
    return exercise(stream, 80);
}

template <>
Result exercise<2021, 6, 2>(std::istream& stream)
{
    return exercise(stream, 256);
}

}
