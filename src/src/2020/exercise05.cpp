#include <array>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

auto toBit(char c)
{
    return (c == 'B') || (c == 'R');
}

auto parseSeatNumber(const std::string& str)
{
    return ranges::accumulate(str | ranges::views::transform(toBit), 0, [](auto&& lhs, auto&& rhs)
    {
        return lhs * 2 + rhs;
    });
}

auto exercise(std::istream& stream)
{
    return ranges::getlines(stream)
            | ranges::views::transform(parseSeatNumber);
}

}

template <>
Result exercise<2020, 5, 1>(std::istream& stream)
{
    return ranges::max(exercise(stream));
}

template <>
Result exercise<2020, 5, 2>(std::istream& stream)
{
    auto ids = exercise(stream)
        | ranges::to_vector
        | ranges::actions::sort
        | ranges::actions::adjacent_remove_if([](auto&& lhs, auto&& rhs) { return lhs + 1 == rhs; });

    return ranges::front(ids) + 1;
}

}
