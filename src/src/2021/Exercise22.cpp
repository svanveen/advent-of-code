#include <regex>
#include <set>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<int, 3>;

struct RebootStep
{
    static RebootStep parse(const std::string& str)
    {
        const auto regex = std::regex{R"(^(on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+)$)"};
        auto match = std::smatch{};
        std::regex_match(str, match, regex);

        return {match[1] == "on", {{std::stoi(match[2]), std::stoi(match[4]), std::stoi(match[6])}}, {{std::stoi(match[3]), std::stoi(match[5]), std::stoi(match[7])}}};
    }

    bool on;
    Position from;
    Position to;
};


}

template <>
Result exercise<2021, 22, 1>(std::istream& stream)
{
    auto rebootSteps = ranges::getlines(stream)
        | ranges::views::transform(RebootStep::parse)
        | ranges::views::filter([](const auto& step) { return step.from[0] >= -50 && step.from[1] >= -50 && step.from[2] >= -50 && step.to[0] <= 50 && step.to[1] <= 50 && step.to[2] <= 50; });

    auto onCubes = std::set<Position>{};
    for (const auto& step : rebootSteps)
    {
        auto positions = ranges::views::cartesian_product
        (
            ranges::views::closed_iota(step.from[0], step.to[0]),
            ranges::views::closed_iota(step.from[1], step.to[1]),
            ranges::views::closed_iota(step.from[2], step.to[2])
        )
        | ranges::views::transform(Position::create<int, int, int>)
        | ranges::to<std::set>;

        if (step.on)
        {
            std::copy(positions.begin(), positions.end(), std::inserter(onCubes, onCubes.begin()));
        }
        else
        {
            auto difference = std::set<Position>{};
            std::set_difference(onCubes.begin(), onCubes.end(), positions.begin(), positions.end(), std::inserter(difference, difference.begin()));
            onCubes = std::move(difference);
        }
    }
    return onCubes.size();
}

template <>
Result exercise<2021, 22, 2>(std::istream& stream)
{
    return 0;
}

}
