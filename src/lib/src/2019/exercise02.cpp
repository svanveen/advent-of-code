#include <string>
#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

template <>
std::size_t exercise<2019, 2, 1>(std::istream& stream)
{
    const IntCodeProgram prog{stream};
    return prog(12, 2);
}

template <>
std::size_t exercise<2019, 2, 2>(std::istream& stream)
{
    const IntCodeProgram prog{stream};

    auto nouns = ranges::views::iota(0, 99);
    auto verbs = ranges::views::iota(0, 99);
    auto solutions = ranges::views::cartesian_product(nouns, verbs)
            | ranges::views::filter([&](auto&& tup) { return prog(std::get<0>(tup), std::get<1>(tup)) == 19690720; })
            | ranges::views::transform([](auto&& tup) { return std::get<0>(tup) * 100 + std::get<1>(tup); });

    return ranges::front(solutions);
}

}
