#include <range/v3/view.hpp>
#include <range/v3/algorithm/max.hpp>
#include <range/v3/algorithm/nth_element.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/ToInts.h>

namespace aoc
{

namespace
{

auto parseCaloriesPerElve(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::split(std::string{})
        | ranges::views::transform([](auto&& rng)
            {
                return ranges::accumulate(rng | utils::toInts, 0);
            });
}

}

template <>
Result exercise<2022, 1, 1>(std::istream& stream)
{
    auto caloriesPerElve = parseCaloriesPerElve(stream);
    return ranges::max(caloriesPerElve);
}

template <>
Result exercise<2022, 1, 2>(std::istream& stream)
{
    auto caloriesPerElve = parseCaloriesPerElve(stream)
        | ranges::to_vector;

    constexpr auto topElveCount = 3;
    ranges::nth_element(caloriesPerElve, std::next(ranges::begin(caloriesPerElve), topElveCount), ranges::greater{});

    return ranges::accumulate(caloriesPerElve | ranges::views::take(topElveCount), 0);

}

}
