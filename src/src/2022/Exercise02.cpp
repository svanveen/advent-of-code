#include <stdexcept>
#include <range/v3/view.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

enum class Shape
{
    rock     = 1,
    paper    = 2,
    scissors = 3
};

Shape operator+(Shape shape, unsigned offset)
{
    return static_cast<Shape>((static_cast<int>(shape) + offset - 1) % 3 + 1);
}

bool operator<(Shape lhs, Shape rhs)
{
    if (lhs == rhs)
    {
        return false;
    }
    return (static_cast<int>(lhs) - static_cast<int>(rhs) + 2) % 3 == 1;
}

struct Round
{
    enum class Outcome
    {
        lose = 0,
        draw  = 3,
        win   = 6,
    };

    Outcome getOutcome() const
    {
        if (opponent == player)
        {
            return Outcome::draw;
        }
        return (opponent < player) ? Outcome::win : Outcome::lose;
    }

    Shape opponent;
    Shape player;
};

Shape parseShape(char c)
{
    switch (c)
    {
        case 'A':
        case 'X':
            return Shape::rock;
        case 'B':
        case 'Y':
            return Shape::paper;
        case 'C':
        case 'Z':
            return Shape::scissors;
        default:
            break;
    }
    throw std::logic_error{"invalid shape"};
}

Round::Outcome parseOutcome(char c)
{
    switch (c)
    {
        case 'X':
            return Round::Outcome::lose;
        case 'Y':
            return Round::Outcome::draw;
        case 'Z':
            return Round::Outcome::win;
        default:
            break;
    }
    throw std::logic_error{"invalid outcome"};
}

int computeScore(const Round& round)
{
    return static_cast<int>(round.player) + static_cast<int>(round.getOutcome());
}

template <typename PARSER>
Result exerciseImpl(std::istream& stream, PARSER&& parser)
{
    return ranges::accumulate
    (
        ranges::getlines(stream) | ranges::views::transform(std::forward<PARSER>(parser)),
        0,
        ranges::plus{},
        computeScore
    );
}

}

template <>
Result exercise<2022, 2, 1>(std::istream& stream)
{
    const auto parseStrategyGuideRound = [](const std::string& str) -> Round
    {
        return {parseShape(str[0]), parseShape(str[2])};
    };
    return exerciseImpl(stream, parseStrategyGuideRound);
}

template <>
Result exercise<2022, 2, 2>(std::istream& stream)
{
    const auto parseStrategyGuideRound = [](const std::string& str) -> Round
    {
        const auto opponent = parseShape(str[0]);
        const auto outcome = parseOutcome(str[2]);
        switch (outcome)
        {
            case Round::Outcome::draw:
                return {opponent, opponent};
            case Round::Outcome::win:
                return {opponent, opponent + 1};
            case Round::Outcome::lose:
                return {opponent, opponent + 2};
            default:
                break;
        }
        throw std::logic_error{"invalid outcome"};
    };
    return exerciseImpl(stream, parseStrategyGuideRound);
}

}
