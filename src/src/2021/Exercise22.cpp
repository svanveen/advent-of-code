#include <regex>
#include <set>
#include <vector>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<long long, 3>;

struct Range
{
    long long from;
    long long to;
};

using Ranges = std::vector<Range>;

struct Cuboid
{
    std::size_t size() const
    {
        return (to[0] - from[0] + 1) * (to[1] - from[1] + 1) * (to[2] - from[2] + 1);
    }

    bool contains(const Position& position) const
    {
        return ranges::all_of(ranges::views::indices(3), [&](auto idx) { return from[idx] <= position[idx] && position[idx] <= to[idx]; });
    }

    bool doIntersect(const Cuboid& other) const
    {
        return ranges::none_of(ranges::views::indices(3), [&](auto idx) { return to[idx] < other.from[idx] || other.to[idx] < from[idx]; });
    }

    std::vector<Cuboid> difference(const Cuboid& other) const
    {
        if (!doIntersect(other))
        {
            return {*this};
        }
        auto ranges = std::array<Ranges, 3>{};
        for (const auto idx : ranges::views::indices(3))
        {
            auto& lhs = (from[idx] <= other.from[idx]) ? (*this) : other;
            auto& rhs = (&lhs != this) ? (*this) : other;

            if (lhs.from[idx] < rhs.from[idx])
            {
                ranges[idx].push_back({lhs.from[idx], rhs.from[idx] - 1});
            }
            if (rhs.to[idx] <= lhs.to[idx])
            {
                ranges[idx].push_back({rhs.from[idx], rhs.to[idx]});
                if (rhs.to[idx] != lhs.to[idx])
                {
                    ranges[idx].push_back({rhs.to[idx] + 1, lhs.to[idx]});
                }
            }
            else
            {
                ranges[idx].push_back({rhs.from[idx], lhs.to[idx]});
                ranges[idx].push_back({lhs.to[idx] + 1, rhs.to[idx]});
            }
        }
        return ranges::views::cartesian_product(ranges[0], ranges[1], ranges[2])
            | ranges::views::filter([&](const auto& tup)
            {
                const auto [rx, ry, rz] = tup;
                const auto tl = Position{{rx.from, ry.from, rz.from}};
                return contains(tl) &&  !other.contains(tl);
            })
            | ranges::views::transform([&](const auto& tup)
            {
                const auto [rx, ry, rz] = tup;
                return Cuboid{{{rx.from, ry.from, rz.from}}, {{rx.to, ry.to, rz.to}}};
            })
            | ranges::to_vector;
    }

    Position from;
    Position to;
};

struct RebootStep : Cuboid
{
    static RebootStep parse(const std::string& str)
    {
        const auto regex = std::regex{R"(^(on|off) x=(-?\d+)..(-?\d+),y=(-?\d+)..(-?\d+),z=(-?\d+)..(-?\d+)$)"};
        auto match = std::smatch{};
        std::regex_match(str, match, regex);

        return {{{{std::stol(match[2]), std::stol(match[4]), std::stol(match[6])}}, {{std::stol(match[3]), std::stol(match[5]), std::stol(match[7])}}}, match[1] == "on"};
    }

    bool on;
};

template <typename FILTER>
Result exercise(std::istream& stream, const FILTER& filter)
{
    auto rebootSteps = ranges::getlines(stream)
        | ranges::views::transform(RebootStep::parse)
        | ranges::views::filter(filter);

    auto cuboids = std::vector<Cuboid>{};
    for (const auto& step : rebootSteps)
    {
        auto newCuboids = std::vector<Cuboid>{};
        for (auto it = cuboids.begin(); it != cuboids.end();)
        {
            if (it->doIntersect(step))
            {
                const auto differenceCuboids = it->difference(step);
                it = cuboids.erase(it);
                newCuboids.reserve(newCuboids.size() + differenceCuboids.size());
                ranges::copy(differenceCuboids, ranges::back_inserter(newCuboids));
            }
            else
            {
                ++it;
            }
        }
        cuboids.reserve(cuboids.size() + newCuboids.size() + 1);
        ranges::copy(newCuboids, ranges::back_inserter(cuboids));
        if (step.on)
        {
            cuboids.push_back(step);
        }
    }
    return ranges::accumulate(cuboids, std::size_t{0}, ranges::plus{}, [](const auto& cuboid) { return cuboid.size(); });
}

}

template <>
Result exercise<2021, 22, 1>(std::istream& stream)
{
    return exercise(stream, [](const auto& step) { return step.from[0] >= -50 && step.from[1] >= -50 && step.from[2] >= -50 && step.to[0] <= 50 && step.to[1] <= 50 && step.to[2] <= 50; });
}

template <>
Result exercise<2021, 22, 2>(std::istream& stream)
{
    return exercise(stream, [](const auto& step) { return true; });
}

}
