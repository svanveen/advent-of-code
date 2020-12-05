#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

auto computeFuel(int mass)
{
    return mass / 3 - 2;
}

int computeFuelRecursive(int mass)
{
    const auto fuel = computeFuel(mass);
    return (fuel > 0) ? fuel + computeFuelRecursive(fuel) : 0;
}

template <typename CALLBACK>
auto exercise(std::istream& stream, CALLBACK&& callback)
{
    auto fuelRequirements = ranges::getlines(stream)
           | ranges::views::filter([](auto&& s) { return !s.empty(); })
           | ranges::views::transform([](auto&& s) { return std::stoull(s); })
           | ranges::views::transform(callback);

    return ranges::accumulate(fuelRequirements, std::size_t{0});
}

}

template <>
Result exercise<2019, 1, 1>(std::istream& stream)
{
    return exercise(stream, computeFuel);
}

template <>
Result exercise<2019, 1, 2>(std::istream& stream)
{
    return exercise(stream, computeFuelRecursive);
}

}
