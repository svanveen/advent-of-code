#include <string>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/ToInts.h>

namespace aoc
{

namespace
{

auto toDigits(std::size_t number)
{
    return ranges::views::iota(0, 6) | ranges::views::transform([=](auto pot) { return (number / static_cast<std::size_t>(std::pow(10, pot))) % 10; });
}

template <typename COMPARATOR>
auto exercise(std::istream& stream)
{
    const auto passwordRange = ranges::getlines(stream, '-')
        | utils::toInts<int>
        | ranges::to_vector;

    const auto& from = passwordRange[0];
    const auto& to = passwordRange[1];

    auto passwords = ranges::views::closed_iota(from, to)
        | ranges::views::transform(toDigits)
        | ranges::views::filter([](auto&& differences) { return ranges::distance(differences) == 6; }, ranges::views::adjacent_filter(ranges::greater_equal{}))
        | ranges::views::filter([](auto&& differences) { return ranges::distance(differences) >= 1; }, ranges::views::group_by(ranges::equal_to{})
                                                                                                                    | ranges::views::transform(ranges::distance)
                                                                                                                    | ranges::views::filter(ranges::bind_back(COMPARATOR{}, 2)));

    return ranges::distance(passwords);
}

}

template <>
Result exercise<2019, 4, 1>(std::istream& stream)
{
    return exercise<ranges::greater_equal>(stream);
}

template <>
Result exercise<2019, 4, 2>(std::istream& stream)
{
    return exercise<ranges::equal_to>(stream);
}

}
