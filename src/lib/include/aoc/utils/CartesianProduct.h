#ifndef ADVENTOFCODE_CARTESIANPRODUCT_H
#define ADVENTOFCODE_CARTESIANPRODUCT_H

namespace aoc::utils
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

}

#endif //ADVENTOFCODE_CARTESIANPRODUCT_H
