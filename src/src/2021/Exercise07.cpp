#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

template <>
Result exercise<2021, 7, 1>(std::istream& stream)
{
    auto positions = ranges::getlines(stream, ',')
        | ranges::views::transform([](auto&& str) { return std::stoi(str); })
        | ranges::to_vector;

    ranges::nth_element(positions, positions.begin() + positions.size() / 2);

    // Since the median is minimizing the L1 norm, this is the optimal solution
    const auto median = positions[positions.size() / 2];

    return ranges::accumulate(positions, 0, ranges::plus{}, [&](auto position)
    {
        return std::abs(position - median);
    });
}

template <>
Result exercise<2021, 7, 2>(std::istream& stream)
{
    auto positions = ranges::getlines(stream, ',')
        | ranges::views::transform([](auto&& str) { return std::stoi(str); })
        | ranges::to_vector;

    // Here also the mean should work somehow since it minimizes the L2 norm and we are trying to minimize L1 + L2 norm
    return ranges::min
    (
        ranges::views::closed_iota(0, *ranges::max_element(positions))
            | ranges::views::transform([&](auto targetPosition)
            {
                return ranges::accumulate(positions, 0, ranges::plus{}, [&](auto position)
                {
                    const auto diff = std::abs(position - targetPosition);
                    return diff * (diff + 1) / 2;
                });
            })
    );
}

}
