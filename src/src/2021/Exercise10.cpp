#include <stack>
#include <variant>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

namespace
{

struct Match
{
    char open;
    char close;
    std::size_t score1;
    std::size_t score2;
};

constexpr auto matches = std::array
{
    Match{'(', ')', 3, 1},
    Match{'[', ']', 57, 2},
    Match{'{', '}', 1197, 3},
    Match{'<', '>', 25137, 4},
};

const Match& getMatch(char c)
{
    return *ranges::find_if(matches, [c](auto&& match)
    {
        return match.open == c || match.close == c;
    });
}

std::variant<std::size_t, std::stack<char>> computeScore(const std::string& str)
{
    auto stack = std::stack<char>{};

    for (const auto& c : str)
    {
        if (const auto& match = getMatch(c); match.open == c)
        {
            stack.push(c);
        }
        else if (match.open == stack.top())
        {
            stack.pop();
        }
        else
        {
            return match.score1;
        }
    }
    return stack;
}

}

template <>
Result exercise<2021, 10, 1>(std::istream& stream)
{
    return ranges::accumulate(ranges::getlines(stream), std::size_t{0}, ranges::plus{}, [](auto&& line)
    {
        return std::visit(utils::overloaded
        {
            [](std::size_t score) { return score; },
            [](const auto&) { return std::size_t{0}; }
        }, computeScore(line));
    });
}

template <>
Result exercise<2021, 10, 2>(std::istream& stream)
{
    auto scores = ranges::getlines(stream)
        | ranges::views::transform(computeScore)
        | ranges::views::filter([](auto&& result) { return std::holds_alternative<std::stack<char>>(result); })
        | ranges::views::transform([](auto&& result)
        {
            auto& stack = std::get<std::stack<char>>(result);
            auto score = std::size_t{};
            while (!stack.empty())
            {
                score = 5 * score + getMatch(stack.top()).score2;
                stack.pop();
            }
            return score;
        })
        | ranges::to_vector;

    ranges::nth_element(scores, ranges::begin(scores) + scores.size() / 2);
    return scores[scores.size() / 2];
}

}
