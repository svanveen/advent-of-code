#include <map>
#include <string>
#include <variant>
#include <aoc/exercises.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace aoc
{

namespace {

struct Range
{
    bool contains(int number) const
    {
        return number >= from && number <= to;
    }

    int from;
    int to;
};

struct Rule
{
    static Rule parse(const std::string& str)
    {
        static const std::regex regex{R"(([\w ]+): (\d+)-(\d+) or (\d+)-(\d+))"};
        std::smatch match;
        if (std::regex_match(str, match, regex))
        {
            return Rule{
                match[1].str(),
                Range{std::stoi(match[2]), std::stoi(match[3])},
                Range{std::stoi(match[4]), std::stoi(match[5])}
            };
        }
        throw std::runtime_error{"could not parse rule"};
    }

    bool accepts(int number) const
    {
        return range1.contains(number) || range2.contains(number);
    }

    std::string field;
    Range range1;
    Range range2;
};

struct Ticket
{
    static Ticket parse(const std::string& str)
    {
        static const std::regex regex{R"(\w+)"};
        auto numbers = str
            | ranges::views::tokenize(regex)
            | ranges::views::transform([](auto&& numberStr) { return std::stoi(numberStr); })
            | ranges::to_vector;
        return Ticket{numbers};
    }

    std::vector<int> numbers;
};

}

template <>
std::size_t exercise<2020, 16, 1>(std::istream& stream)
{
    auto lineGroups = ranges::getlines(stream)
        | ranges::views::split("");

    auto lineGroupIt = lineGroups.begin();

    const auto rules = *lineGroupIt
        | ranges::views::transform(Rule::parse)
        | ranges::to_vector;
    lineGroupIt++;

    lineGroupIt++;

    const auto nearbyTickets = *lineGroupIt
        | ranges::views::drop(1)
        | ranges::views::transform(Ticket::parse)
        | ranges::to_vector;

    auto acceptedByNoRule = [&](auto&& number)
    {
        return ranges::none_of(rules, [&](auto&& rule) { return rule.accepts(number); });
    };

    auto getAcceptedNumbers = [&](auto&& ticket)
    {
        return ticket.numbers | ranges::views::filter(acceptedByNoRule);
    };

    auto notAcceptedNumbers = nearbyTickets
        | ranges::views::transform(getAcceptedNumbers)
        | ranges::views::join;

    return ranges::accumulate(notAcceptedNumbers, 0);
}

template <>
std::size_t exercise<2020, 16, 2>(std::istream& stream)
{
    return 0;
}

}
