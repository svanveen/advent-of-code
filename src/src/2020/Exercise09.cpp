#include <string>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/ToInts.h>

namespace aoc
{

namespace
{

auto getNumbers(std::istream& stream)
{
    return ranges::getlines(stream)
        | utils::toInts<unsigned long long>
        | ranges::to_vector;
}

auto getInvalidNumber(const std::vector<std::size_t>& numbers, int preamble)
{
    auto result = numbers
        | ranges::views::sliding(preamble + 1)
        | ranges::views::filter([](auto&& rng)
            {
                auto& el = ranges::back(rng);
                auto x = rng | ranges::views::drop_last(1);
                return ranges::distance(ranges::views::cartesian_product(x, x)
                    | ranges::views::filter([](auto&& tup) { return std::get<0>(tup) != std::get<1>(tup); })
                    | ranges::views::filter([el](auto&& tup) { return std::get<0>(tup) + std::get<1>(tup) == el; })) == 0;
            })
        | ranges::views::transform(ranges::back);

    return ranges::front(result);
}

}

template <>
Result exercise<2020, 9, 1>(std::istream& stream)
{
    auto numbers = getNumbers(stream);
    return getInvalidNumber(numbers, 25);
}

template <>
Result exercise<2020, 9, 2>(std::istream& stream)
{
    const auto numbers = getNumbers(stream);
    const auto invalidNumber = getInvalidNumber(numbers, 25);

    auto rng = ranges::views::iota(0u, numbers.size())
        | ranges::views::transform([&](auto idx)
            {
                auto partialSum = numbers
                    | ranges::views::drop(idx)
                    | ranges::views::partial_sum
                    | ranges::views::take_while(ranges::bind_back(ranges::less_equal{}, invalidNumber));

                return numbers | ranges::views::drop(idx) | ranges::views::take(ranges::distance(partialSum));
            })
        | ranges::views::filter(ranges::bind_back(ranges::greater{}, 1), ranges::distance)
        | ranges::views::filter(ranges::bind_back(ranges::equal_to{}, invalidNumber), ranges::bind_back(ranges::accumulate, 0));

    auto encryptionWeakness = ranges::front(rng);
    std::cout << ranges::distance(rng) << std::endl;
    return ranges::min(encryptionWeakness) + ranges::max(encryptionWeakness);
}

}
