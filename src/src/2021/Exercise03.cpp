#include <bitset>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

char mostCommon(const std::vector<std::string>& report, std::size_t idx)
{
    const auto count = ranges::distance
    (
        report | ranges::views::filter([idx](const auto& str) { return str[idx] == '1'; })
    );
    return (2 * count >= report.size()) ? '1' : '0';
}

auto toDecimal(const std::string& str)
{
    return std::bitset<16>{str}.to_ulong();
}

}

template <>
Result exercise<2021, 3, 1>(std::istream& stream)
{
    const auto report = ranges::getlines(stream) | ranges::to_vector;
    const auto bits = report.front().size();

    const auto gamma = toDecimal
    (
        ranges::views::indices(std::size_t{0}, bits)
            | ranges::views::transform([&](auto idx) { return mostCommon(report, idx); })
            | ranges::to<std::string>
    );

    return gamma * (std::pow(2, bits) - 1 - gamma);
}

template <>
Result exercise<2021, 3, 2>(std::istream& stream)
{
    auto report = ranges::getlines(stream) | ranges::to_vector;

    auto computeRating = [](auto report, auto&& comp)
    {
        for (std::size_t idx = 0; report.size() > 1; ++idx)
        {
            auto common = mostCommon(report, idx);
            report = std::move(report)
                | ranges::actions::remove_if([&](const auto& str) { return comp(str[idx], common); });
        }
        return toDecimal(report.front());
    };

    return computeRating(report, ranges::equal_to{}) * computeRating(report, ranges::not_equal_to{});
}

}
