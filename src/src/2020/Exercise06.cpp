#include <array>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

template <typename FILTER>
auto exercise(std::istream& stream, FILTER&& filter)
{
    auto lines =  ranges::getlines(stream) | ranges::to_vector;

    auto answers = lines
        | ranges::views::split_when([](auto&& line) { return line.empty(); })
        | ranges::views::transform([filter](auto&& passengers)
            {
                return ranges::views::iota('a', 'z' + 1)
                    | ranges::views::filter([filter, passengers](auto&& q)
                        {
                            return filter(passengers, [q](auto&& str) { return str.find(q) != std::string::npos; });
                        });
            })
        | ranges::views::transform(ranges::distance);

    return ranges::accumulate(answers, std::size_t{0});
}

}

template <>
Result exercise<2020, 6, 1>(std::istream& stream)
{
    return exercise(stream, ranges::any_of);
}

template <>
Result exercise<2020, 6, 2>(std::istream& stream)
{
    return exercise(stream, ranges::all_of);
}

}
