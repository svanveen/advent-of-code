#include <regex>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <range/v3/numeric/accumulate.hpp>

namespace aoc
{

namespace
{

struct Player
{
    int roll(int number)
    {
        position = (position + number - 1) % 10 + 1;
        return score += position;
    }

    int position;
    int score = 0;
};


auto parsePlayers(std::istream& stream)
{
    auto lines = ranges::getlines(stream);
    constexpr auto parseStartingPoint([](const auto& str)
    {
        const auto regex = std::regex{R"(Player \d starting position: (\d+))"};
        auto match = std::smatch{};
        std::regex_match(str, match, regex);
        return Player{std::stoi(match[1])};
    });

    return std::array
    {
        parseStartingPoint(*lines.begin()),
        parseStartingPoint(*ranges::next(lines.begin()))
    };
}

}

template <>
Result exercise<2021, 21, 1>(std::istream& stream)
{
    auto players = parsePlayers(stream);

    auto rollSums = ranges::views::closed_iota(1, 100)
        | ranges::views::cycle
        | ranges::views::chunk(3)
        | ranges::views::transform([](auto&& rng) { return ranges::accumulate(rng, std::size_t{0}); });

    auto rounds = 1;
    for (const auto number : rollSums)
    {
        const auto idx = (rounds - 1) % 2;
        if (players[idx].roll(number) >= 1000)
        {
            return players[1 - idx].score * rounds * 3;
        }
        ++rounds;
    }
    return 0;
}

template <>
Result exercise<2021, 21, 2>(std::istream& stream)
{
    return 0;
}

}
