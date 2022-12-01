#include <map>
#include <string>
#include <variant>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/ToInts.h>

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
                       | utils::toInts<int>
                       | ranges::to_vector;
        return Ticket{numbers};
    }

    std::vector<int> numbers;
};

auto parseInput(std::istream& stream)
{
    auto lineGroups = ranges::getlines(stream)
        | ranges::views::split("");

    auto lineGroupIt = lineGroups.begin();

    const auto rules = *lineGroupIt
        | ranges::views::transform(Rule::parse)
        | ranges::to_vector;

    const auto myTickets = *(++lineGroupIt)
        | ranges::views::drop(1)
        | ranges::views::transform(Ticket::parse)
        | ranges::to_vector;

    const auto nearbyTickets = *(++lineGroupIt)
        | ranges::views::drop(1)
        | ranges::views::transform(Ticket::parse)
        | ranges::to_vector;

    return std::tuple{rules, myTickets, nearbyTickets};
}

}

template <>
Result exercise<2020, 16, 1>(std::istream& stream)
{
    const auto [rules, _, nearbyTickets] = parseInput(stream);

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
Result exercise<2020, 16, 2>(std::istream& stream)
{
    const auto [rules, myTickets, nearbyTickets] = parseInput(stream);

    auto acceptedByAnyRule = [&](auto&& number)
    {
        return ranges::any_of(rules, [&](auto&& rule) { return rule.accepts(number); });
    };

    auto isValid = [&](auto&& ticket)
    {
        return ranges::all_of(ticket.numbers, acceptedByAnyRule);
    };

    auto validTickets = ranges::views::concat(myTickets, nearbyTickets)
        | ranges::views::filter(isValid)
        | ranges::to_vector;

    const auto& myTicket = validTickets[0];

    auto accepts = [&](auto&& ticket, auto&& tuple) {
        const auto& [idx, rule] = tuple;
        return rule.accepts(ticket.numbers[idx]);
    };
    auto acceptsAll = [&](auto&& tuple)
    {
        return ranges::all_of(validTickets, ranges::bind_back(accepts, tuple));
    };

    auto validCombinationsPerIdx = ranges::views::cartesian_product(ranges::views::indices(std::size_t{0}, myTicket.numbers.size()), rules)
        | ranges::views::filter(acceptsAll)
        | ranges::views::group_by([](auto&& lhs, auto&& rhs)
            {
                return std::get<0>(lhs) == std::get<0>(rhs);
            })
        | ranges::to_vector
        | ranges::actions::sort([](auto&& lhs, auto&& rhs) { return ranges::distance(lhs) < ranges::distance(rhs); });

    std::map<std::string, bool> isSet;
    std::size_t result = 1;

    // Assumption is that the valid combination have increasing sizes starting with 1
    for (auto&& cmb : validCombinationsPerIdx)
    {
        for (auto&& tuple : cmb)
        {
            const auto& [idx, rule] = tuple;
            if (!isSet[rule.field])
            {
                isSet[rule.field] = true;
                if (rule.field.find("departure") == 0)
                {
                    result *= myTicket.numbers[idx];
                }
            }
        }
    }
    return result;
}

}
