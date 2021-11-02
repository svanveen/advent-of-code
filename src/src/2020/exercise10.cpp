#include <string>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercise.h>
#include <range/v3/numeric/accumulate.hpp>

namespace aoc
{

namespace
{

auto adjacentDifferenceEquals(std::size_t value)
{
    return ranges::views::adjacent_filter([=](auto&& lhs, auto&& rhs) { return rhs - lhs == value; }) | ranges::views::drop(1);
}

auto countPossibleCombinations(const std::vector<std::size_t>& numbers, std::vector<std::size_t>& resultCache, std::size_t index)
{
    const auto el = numbers.at(index);
    if (index + 1 == numbers.size())
    {
        return std::size_t{1};
    }
    auto successors = ranges::views::iota(index + 1, numbers.size())
        | ranges::views::take_while([&](auto&& idx) { return numbers[idx] - el <= 3; })
        | ranges::views::transform([&](auto&& idx)
            {
                if (resultCache[idx] == 0)
                {
                    resultCache[idx] = countPossibleCombinations(numbers, resultCache, idx);
                }
                return resultCache[idx];
            });

    return ranges::accumulate(successors, std::size_t{0});
}

auto countPossibleCombinations(const std::vector<std::size_t>& numbers, std::size_t index = 0)
{
    auto resultCache = std::vector<std::size_t>(numbers.size(), 0);
    return countPossibleCombinations(numbers, resultCache, index);
}

auto getNumbers(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform([](auto&& str) { return std::stoull(str); })
        | ranges::to_vector
        | ranges::actions::push_back(std::size_t{0})
        | ranges::actions::sort;
}

}

template <>
Result exercise<2020, 10, 1>(std::istream& stream)
{
    const auto numbers = getNumbers(stream);
    auto dist1 = numbers | adjacentDifferenceEquals(1);
    auto dist3 = numbers | adjacentDifferenceEquals(3);

    // +1 for missing largest element
    return ranges::distance(dist1) * (ranges::distance(dist3) + 1);
}

template <>
Result exercise<2020, 10, 2>(std::istream& stream)
{
    const auto numbers = getNumbers(stream);

    return countPossibleCombinations(numbers);
}

}
