#ifndef ADVENT_OF_CODE_DAY01_H
#define ADVENT_OF_CODE_DAY01_H

#include <fstream>
#include <string>
#include <range/v3/view.hpp>
#include <range/v3/range/operations.hpp>
#include <range/v3/utility/tuple_algorithm.hpp>

namespace day1
{

namespace impl
{

template <typename R, std::size_t N, std::size_t ...INDICES>
auto cartesian_product(const std::array<const R*, N>& array, std::index_sequence<INDICES...>)
{
    return ranges::views::cartesian_product(*std::get<INDICES>(array)...);
}

template <std::size_t N, typename R>
auto cartesian_product(const R& r)
{
    std::array<const R*, N> array;
    array.fill(&r);
    return cartesian_product(array, std::make_index_sequence<N>{});
}

template <std::size_t N>
auto exercise(const std::string& path)
{
    std::ifstream stream{path};
    const auto numbers = ranges::getlines(stream)
           | ranges::views::filter([](auto&& s) { return !s.empty(); })
           | ranges::views::transform([](auto&& s) { return std::stoi(s); })
           | ranges::to_vector;

    auto solutions = cartesian_product<N + 1>(numbers)
        | ranges::views::filter([](auto&& tup) { return ranges::tuple_foldl(tup, 0, std::plus{}) == 2020; })
        | ranges::views::transform([](auto&& tup) { return ranges::tuple_foldl(tup, 1, std::multiplies{}); });

    return ranges::front(solutions);
}

}

auto exercise1(const std::string& path)
{
    return impl::exercise<1>(path);
}

auto exercise2(const std::string& path)
{
    return impl::exercise<2>(path);
}

}


#endif //ADVENT_OF_CODE_DAY01_H
