#include <queue>
#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct CardDeck : std::deque<int>
{
    template <typename It>
    CardDeck(It start, It end)
        : std::deque<int>(start, end)
    {}

    using std::deque<int>::empty;
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

auto playGameOfCombat(CardDeck playerA, CardDeck playerB)
{
    while (!(playerA.empty() || playerB.empty()))
    {
        const auto a = playerA.pop();
        const auto b = playerB.pop();
        if (a > b)
        {
            playerA.push(a);
            playerA.push(b);
        }
        else
        {
            playerB.push(b);
            playerB.push(a);
        }
    }

    if (!playerA.empty())
    {
        return playerA.result();
    }
    else
    {
        return playerB.result();
    }
}

}

template <>
std::size_t exercise<2020, 22, 1>(std::istream& stream)
{
    auto [playerA, playerB] = getPlayersCards(stream);

    return playGameOfCombat(playerA, playerB);
}

template <>
std::size_t exercise<2020, 22, 2>(std::istream& stream)
{
    return 0;
}

}
