#include <string>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/CartesianProduct.h>

namespace aoc
{

namespace
{


template <std::size_t N>
auto exercise(std::istream& stream)
{
    const auto numbers = ranges::getlines(stream)
           | ranges::views::filter([](auto&& s) { return !s.empty(); })
           | ranges::views::transform([](auto&& s) { return std::stoi(s); })
           | ranges::to_vector;

    auto solutions = utils::cartesian_product<N + 1>(numbers)
        | ranges::views::filter([](auto&& tup) { return ranges::tuple_foldl(tup, 0, std::plus{}) == 2020; })
        | ranges::views::transform([](auto&& tup) { return ranges::tuple_foldl(tup, 1, std::multiplies{}); });

    return ranges::front(solutions);
}

}

template <>
std::size_t exercise<2020, 1, 1>(std::istream& stream)
{
    return exercise<1>(stream);
}

template <>
std::size_t exercise<2020, 1, 2>(std::istream& stream)
{
    return exercise<2>(stream);
}

}
