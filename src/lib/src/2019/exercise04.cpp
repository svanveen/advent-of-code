#include <string>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

auto toDigits(std::size_t number)
{
    return ranges::views::iota(0, 6) | ranges::views::transform([=](auto pot) { return (number / static_cast<std::size_t>(std::pow(10, pot))) % 10; });
}

auto exercise(std::istream& stream)
{
    const auto passwordRange = ranges::getlines(stream, '-')
        | ranges::views::transform([](auto&& str) { return std::stoi(str); })
        | ranges::to_vector;

    const auto& from = passwordRange[0];
    const auto& to = passwordRange[1];

    auto passwords = ranges::views::iota(from, to + 1)
        | ranges::views::transform(toDigits)
        | ranges::views::filter([](auto&& differences) { return ranges::distance(differences) == 6; }, ranges::views::adjacent_filter(ranges::greater_equal{}))
        | ranges::views::filter([](auto&& differences) { return ranges::distance(differences) >= 2; }, ranges::views::adjacent_filter(ranges::equal_to{}));

    return ranges::distance(passwords);
}

}

template <>
std::size_t exercise<2019, 4, 1>(std::istream& stream)
{
    return exercise(stream);
}

template <>
std::size_t exercise<2019, 4, 2>(std::istream& stream)
{
    return 0;
}

}
