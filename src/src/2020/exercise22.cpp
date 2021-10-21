#include <queue>
#include <string>
#include <vector>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

enum class Player
{
    A,
    B,
};

struct Result
{
    Player winner;
    int score;
};

struct CardDeck : std::deque<int>
{
    template <typename It>
    CardDeck(It start, It end)
        : std::deque<int>(start, end)
    {}

    using std::deque<int>::empty;
    using std::deque<int>::size;
    using std::deque<int>::begin;
    using std::deque<int>::end;

    int pop()
    {
        auto el = this->front();
        this->pop_front();
        return el;
    }

    void push(int el)
    {
        this->push_back(el);
    }

    CardDeck subset(int count)
    {
        auto cards = (*this) | ranges::views::take(count);
        return {cards.begin(), cards.end()};
    }

    int result() const
    {
        return ranges::inner_product(
            ranges::views::closed_iota(1, static_cast<int>(this->size())) | ranges::views::reverse,
            *this,
            0
        );
    }
};

auto getPlayersCards(std::istream& stream)
{
    auto playersCards = ranges::getlines(stream)
        | ranges::views::split("")
        | ranges::views::transform([](auto&& rng)
            {
                auto numbers = rng
                    | ranges::views::drop(1)
                    | ranges::views::transform([](auto&& number) { return std::stoi(number); })
                    | ranges::views::common;
                return CardDeck{numbers.begin(), numbers.end()};
            }
    );

    return std::pair{*playersCards.begin(), *++playersCards.begin()};
}

Result playGameOfCombat(CardDeck playerA, CardDeck playerB, bool recursive = false)
{
    auto appendToWinner = [&](Player winner, int a, int b)
    {
        if (Player::A == winner)
        {
            playerA.push(a);
            playerA.push(b);
        }
        else
        {
            playerB.push(b);
            playerB.push(a);
        }
    };

    std::vector<CardDeck> historyPlayerA;
    std::vector<CardDeck> historyPlayerB;
    while (!(playerA.empty() || playerB.empty()))
    {
        if (ranges::find(historyPlayerA, playerA) != std::end(historyPlayerA) &&
            ranges::find(historyPlayerB, playerB) != std::end(historyPlayerB))
        {
            return {Player::A, playerA.result()};
        }
        historyPlayerA.push_back(playerA);
        historyPlayerB.push_back(playerB);

        const auto a = playerA.pop();
        const auto b = playerB.pop();
        if (recursive && (a <= playerA.size()) && (b <= playerB.size()))
        {
            auto [winner, _] = playGameOfCombat(playerA.subset(a), playerB.subset(b), recursive);
            appendToWinner(winner, a, b);
        }
        else if (a > b)
        {
            appendToWinner(Player::A, a, b);
        }
        else
        {
            appendToWinner(Player::B, a, b);
        }
    }

    if (!playerA.empty())
    {
        return {Player::A, playerA.result()};
    }
    else
    {
        return {Player::B, playerB.result()};
    }
}

}

template <>
std::size_t exercise<2020, 22, 1>(std::istream& stream)
{
    auto [playerA, playerB] = getPlayersCards(stream);

    return playGameOfCombat(playerA, playerB).score;
}

template <>
std::size_t exercise<2020, 22, 2>(std::istream& stream)
{
    auto [playerA, playerB] = getPlayersCards(stream);

    return playGameOfCombat(playerA, playerB, true).score;
}

}
