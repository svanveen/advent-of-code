#include <string>
#include <variant>
#include <aoc/exercises.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <range/v3/iterator_range.hpp>

namespace aoc
{

namespace
{

auto exercise(std::istream& stream, std::size_t N)
{
    auto numbers = ranges::getlines(stream, ',')
        | ranges::views::transform([](auto&& number) { return std::stoull(number); })
        | ranges::to_vector;
    numbers.reserve(N);

    for (auto i = numbers.size(); i < N; ++i)
    {
        const auto it = find(std::next(std::rbegin(numbers)), std::rend(numbers), numbers[i - 1]);
        if (it == std::rend(numbers))
        {
            numbers.push_back(0);
        }
        else
        {
            numbers.push_back(std::distance(std::rbegin(numbers), it));
        }
    }
    return numbers.back();
}

}

template <>
std::size_t exercise<2020, 15, 1>(std::istream& stream)
{
    return exercise(stream, 2020);
}

template <>
std::size_t exercise<2020, 15, 2>(std::istream& stream)
{
    return 0;
}

}
