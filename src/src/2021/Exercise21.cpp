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

using Players = std::array<Player, 2>;
using Wins = std::array<std::size_t, 2>;

Wins playDiracDie(const Players& players, std::size_t player = 0, std::size_t cardinality = 1)
{
    struct Roll
    {
        int value;
        std::size_t cardinality;
    };
    constexpr auto rolls = std::array
    {
        Roll{3, 1},
        Roll{4, 3},
        Roll{5, 6},
        Roll{6, 7},
        Roll{7, 6},
        Roll{8, 3},
        Roll{9, 1}
    };

    auto wins = Wins{};
    for (const auto& roll : rolls)
    {
        auto p = players;
        if (p[player].roll(roll.value) >= 21)
        {
            wins[player] += cardinality * roll.cardinality;
        }
        else
        {
            const auto subwins = playDiracDie(p, 1 - player, cardinality * roll.cardinality);
            wins[0] += subwins[0];
            wins[1] += subwins[1];
        }
    }
    return wins;
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
    auto players = parsePlayers(stream);
    const auto[winsPlayer1, winsPlayer2] = playDiracDie(players);
    return std::max(winsPlayer1, winsPlayer2);
}

}
