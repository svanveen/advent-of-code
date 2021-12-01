#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

auto getDepths(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform([](auto&& str) { return std::stoi(str); })
        | ranges::to_vector;
}

}

template <>
Result exercise<2021, 1, 1>(std::istream& stream)
{
    const auto depths = getDepths(stream);
    return ranges::distance
    (
        depths
            | ranges::views::adjacent_filter([](auto&& lhs, auto&& rhs) { return lhs < rhs; })
            | ranges::views::drop(1)
    );
}

template <>
Result exercise<2021, 1, 2>(std::istream& stream)
{
    const auto depths = getDepths(stream);
    return ranges::distance
    (
        depths
            | ranges::views::sliding(3)
            | ranges::views::transform(ranges::bind_back(ranges::accumulate, 0))
            | ranges::views::adjacent_filter([](auto&& lhs, auto&& rhs) { return lhs < rhs; })
            | ranges::views::drop(1)
    );
}

}
