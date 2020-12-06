#include <regex>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Point
{
    int x = 0;
    int y = 0;

    static auto createSteps(const std::string& str)
    {
        static const auto regex = std::regex{R"((\w)(\d+))"};
        std::smatch match;
        std::regex_match(str, match, regex);
        auto steps = std::stoi(match[2]);
        switch (*match[1].first)
        {
            case 'R': return ranges::views::repeat_n(Point{+1, 0}, steps);
            case 'L': return ranges::views::repeat_n(Point{-1, 0}, steps);
            case 'U': return ranges::views::repeat_n(Point{0, +1}, steps);
            case 'D': return ranges::views::repeat_n(Point{0, -1}, steps);
            default: throw std::runtime_error{"wrong direction"};
        }
    }

    constexpr static std::size_t dist(const Point& p)
    {
        return std::abs(p.x) + std::abs(p.y);
    }

    constexpr bool operator<=(const Point& other) const { return (x < other.x) || (x == other.x && y <= other.y); }
    constexpr bool operator>=(const Point& other) const { return (x > other.x) || (x == other.x && y >= other.y); }
    constexpr bool operator<(const Point& other) const { return (*this <= other) && !(other <= *this); }
    constexpr bool operator>(const Point& other) const { return (*this >= other) && !(other >= *this); }
    constexpr bool operator==(const Point& other) const { return (*this <= other) && (other <= *this); }
    constexpr bool operator!=(const Point& other) const { return !(*this == other); }

    constexpr Point operator+(const Point& other) const
    {
        return {x + other.x, y + other.y};
    }
};

auto computePoints(std::istream& stream)
{
    std::string line;
    if (!std::getline(stream, line))
    {
        throw std::runtime_error{"no line to read"};
    }
    return line
        | ranges::views::tokenize(std::regex{R"([^,]+)"}, 0, std::regex_constants::match_not_null)
        | ranges::views::transform(Point::createSteps)
        | ranges::views::join
        | ranges::views::partial_sum
        | ranges::to_vector;
}

template <int EXERCISE>
auto exercise(std::istream& stream)
{
    auto points1 = computePoints(stream);
    auto points2 = computePoints(stream);

    auto sorted1 = points1 | ranges::to_vector | ranges::actions::sort;
    auto sorted2 = points2 | ranges::to_vector | ranges::actions::sort;
    auto intersections = ranges::views::set_intersection(sorted1, sorted2);

    if constexpr (1 == EXERCISE)
    {
        return ranges::min(intersections | ranges::views::transform(Point::dist));
    }
    else
    {
        return ranges::min(intersections | ranges::views::transform([&](auto&& intersection)
            {
                const auto stepsToIntersection = [](auto&& points, auto&& intersection)
                {
                    return ranges::distance(points | ranges::views::take_while([&](auto&& point) { return point != intersection; })) + 1;
                };
                return stepsToIntersection(points1, intersection) + stepsToIntersection(points2, intersection);
            }));
    }
}

}

template <>
Result exercise<2019, 3, 1>(std::istream& stream)
{
    return exercise<1>(stream);
}

template <>
Result exercise<2019, 3, 2>(std::istream& stream)
{
    return exercise<2>(stream);
}

}
