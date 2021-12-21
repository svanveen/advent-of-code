#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Position
{
    int x;
    int y;
    int z;
};

class Scanner
{
public:
    template <typename RNG>
    static Scanner parse(RNG&& rng)
    {
        constexpr auto parsePosition = [](const std::string& str)
        {
            const auto regex = std::regex{R"((-?\d+),(-?\d+),(-?\d+))"};
            auto match = std::smatch{};

            std::regex_match(str, match, regex);
            return Position{std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3])};
        };

        return Scanner{
            rng
                | ranges::views::drop(1)
                | ranges::views::transform(parsePosition)
                | ranges::to_vector
        };
    }

private:
    explicit Scanner(std::vector<Position> beacons)
        : beacons(std::move(beacons))
    {}

private:
    std::vector<Position> beacons;
};

}

template <>
Result exercise<2021, 19, 1>(std::istream& stream)
{
    const auto scanners = ranges::getlines(stream)
        | ranges::views::split(std::string{})
        | ranges::views::transform([](auto&& rng) { return Scanner::parse(std::forward<decltype(rng)>(rng)); })
        | ranges::to_vector;
    return 0;
}

template <>
Result exercise<2021, 19, 2>(std::istream& stream)
{
    return 0;
}

}
