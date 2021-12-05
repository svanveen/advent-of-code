#include <regex>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Point = utils::Position<int, 2>;

struct Line
{
    static Line parse(const std::string& str)
    {
        auto regex = std::regex{R"(^(\d+),(\d+) -> (\d+),(\d+)$)"};
        auto match = std::smatch{};

        std::regex_match(str, match, regex);

        return {{{std::stoi(match[1]), std::stoi(match[2])}}, {{std::stoi(match[3]), std::stoi(match[4])}}};
    }

    bool isStraight() const
    {
        return a[0] == b[0] || a[1] == b[1];
    }

    auto getPoints() const
    {
        const auto dir = b - a;
        const auto dist = std::max(std::abs(dir[0]), std::abs(dir[1]));

        return ranges::views::closed_iota(0, dist)
            | ranges::views::transform([start = a, dir = dir/dist](auto&& factor)
            {
                return start + factor * dir;
            });
    }

    Point a;
    Point b;
};

template <typename FILTER>
Result exercise(std::istream& stream, FILTER&& filter)
{
    auto points = ranges::getlines(stream)
        | ranges::views::transform(Line::parse)
        | ranges::views::filter(std::forward<FILTER>(filter))
        | ranges::views::transform([](auto&& line) { return line.getPoints(); })
        | ranges::views::join
        | ranges::to_vector
        | ranges::actions::sort;

    auto intersections = points
        | ranges::views::group_by(ranges::equal_to{})
        | ranges::views::filter(ranges::bind_back(ranges::greater_equal{}, 2), ranges::distance);

    return ranges::distance(intersections);
}

}

template <>
Result exercise<2021, 5, 1>(std::istream& stream)
{
    return exercise(stream, [](auto&& line) { return line.isStraight(); });
}

template <>
Result exercise<2021, 5, 2>(std::istream& stream)
{
    return exercise(stream, [](auto&& line) { return true; });
}

}
