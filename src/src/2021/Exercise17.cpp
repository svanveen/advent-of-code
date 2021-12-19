#include <regex>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Rectangle
{
    struct Range
    {
        bool contains(int value) const
        {
            return from <= value && value <= to;
        }

        int from;
        int to;
    };

    static Rectangle parse(const std::string& str)
    {
        const auto regex = std::regex{R"(target area: x=(-?\d+)..(-?\d+), y=(-?\d+)..(-?\d+))"};
        auto match = std::smatch{};
        std::regex_match(str, match, regex);

        return {{std::stoi(match[1]), std::stoi(match[2])}, {std::stoi(match[3]), std::stoi(match[4])}};
    }
    int left() const { return x.from; };
    int right() const { return x.to; };
    int bottom() const { return y.from; };
    int top() const { return y.to; };

    Range x;
    Range y;
};

constexpr auto fx = [](int n, int dx)
{
    const auto N = std::min(std::abs(dx), n); // |dx| does not drop below 0
    if (dx > 0)
    {
        return n * (dx + 1) - (N * (N + 1)) / 2;
    }
    else if (dx < 0)
    {
        return n * (dx - 1) + (N * (N + 1)) / 2;
    }
    return 0;
};

constexpr auto fy = [](int n, int dy)
{
    return n * (dy + 1) - (n * (n + 1)) / 2;
};

int hits(const Rectangle& rect, int dx, int dy)
{
    auto x = 0;
    auto y = 0;
    for (const auto n : ranges::views::iota(1))
    {
        x += dx;
        y += dy;
        if (dx > 0)
        {
            --dx;
        }
        else if (dx < 0)
        {
            ++dx;
        }
        --dy;

        if (rect.x.contains(x) && rect.y.contains(y))
        {
            return true;
        }
        if (x > rect.right() || y < rect.bottom())
        {
            return false;
        }
    }
}

}

template <>
Result exercise<2021, 17, 1>(std::istream& stream)
{
    const auto rect = Rectangle::parse(*ranges::getlines(stream).begin());

    auto highestPoints = ranges::views::iota(rect.bottom())
        | ranges::views::take_while([&](const auto dy)
        {
            return ranges::any_of
            (
                ranges::views::closed_iota(std::min(rect.left(), 0), std::max(rect.right(), 0)),
                [&](const auto dx) { return hits(rect, dx, dy); }
            );
        })
        | ranges::views::transform([&](const auto dy)
        {
            return (dy * (dy + 1)) / 2;
        });

    return ranges::max(highestPoints);
}

template <>
Result exercise<2021, 17, 2>(std::istream& stream)
{
    const auto rect = Rectangle::parse(*ranges::getlines(stream).begin());

    auto velocityCounts = ranges::views::iota(rect.bottom())
        | ranges::views::transform([&](const auto dy)
        {
            return ranges::distance
            (
                ranges::views::closed_iota(std::min(rect.left(), 0), std::max(rect.right(), 0))
                    | ranges::views::filter([&](const auto dx) { return hits(rect, dx, dy); })
            );
        })
        | ranges::views::take_while(ranges::bind_back(ranges::greater{}, 0));

    return ranges::accumulate(velocityCounts, std::size_t{0});
}

}
