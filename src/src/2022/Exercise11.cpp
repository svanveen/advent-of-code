#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/qi.hpp>
#include <range/v3/algorithm/partial_sort.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

using WorryLevel = unsigned long long;

struct Monkey
{
    Monkey(std::vector<WorryLevel> items, char op, boost::optional<int> factor, int divisibleBy, int targetIf, int targetElse)
        : items(std::move(items))
        , operation([&]() -> std::function<WorryLevel(WorryLevel)>
            {
                if (op == '*' && factor)
                {
                    return [=](WorryLevel level) { return level * *factor; };
                }
                if (op == '+' && factor)
                {
                    return [=](WorryLevel level) { return level + *factor; };
                }
                if (op == '*' && !factor)
                {
                    return [=](WorryLevel level) { return level * level; };
                }
                if (op == '+' && !factor)
                {
                    return [=](WorryLevel level) { return level + level; };
                }
                throw std::logic_error{"invalid operation"};
            }())
        , throwTarget([=](WorryLevel level) { return (level % divisibleBy == 0) ? targetIf : targetElse; })
        , congruenceClass(divisibleBy)
    {}

    void inspect(WorryLevel& item)
    {
        item = operation(item);
        ++inspected;
    }

    std::vector<WorryLevel> items;
    std::function<WorryLevel(WorryLevel)> operation;
    std::function<int(WorryLevel)> throwTarget;
    int congruenceClass;
    std::size_t inspected = 0;
};

using Monkeys = std::vector<Monkey>;

Monkeys parseMonkeys(std::istream& stream)
{
    auto monkeys = Monkeys{};
    for (const auto& block : ranges::getlines(stream) | ranges::views::split(std::string{}))
    {
        auto bytes = block
            | ranges::views::join
            | ranges::views::common
            | ranges::to<std::string>; // TODO: get rid of this

        
        const auto addMonkey = [&](std::vector<WorryLevel> items, char op, boost::optional<int> factor, int divisibleBy, int targetIf, int targetElse)
        {
            monkeys.emplace_back(items, op, factor, divisibleBy, targetIf, targetElse);
        };

        using namespace boost::phoenix;
        using namespace boost::spirit;
        auto rule = (
            qi::lit("Monkey ") >> qi::omit[qi::int_] >> ':'
                >> qi::lit("  Starting items: ")             >> (qi::ulong_long % qi::lit(", "))
                >> qi::lit("  Operation: new = old ")        >> (qi::char_("+*") >> ' ' >> (qi::int_ | qi::lit("old")))
                >> qi::lit("  Test: divisible by ")          >> qi::int_
                >> qi::lit("    If true: throw to monkey ")  >> qi::int_
                >> qi::lit("    If false: throw to monkey ") >> qi::int_
        )[bind(addMonkey, qi::_1, qi::_2, qi::_3, qi::_4, qi::_5, qi::_6)];

        if (!qi::parse(ranges::begin(bytes), ranges::end(bytes), rule))
        {
            throw std::logic_error{"could not parse monkey"};
        }
    }
    return monkeys;
}

Result exercise(std::istream& stream, std::size_t rounds, unsigned reliefFactor)
{
    auto monkeys = parseMonkeys(stream);
    auto congruenceClass = ranges::accumulate(monkeys, 1, ranges::multiplies{}, &Monkey::congruenceClass);
    for (auto round : ranges::views::indices(rounds))
    {
        for (auto& monkey : monkeys)
        {
            for (auto& item : monkey.items)
            {
                monkey.inspect(item);
                item /= reliefFactor;
                item %= congruenceClass;
                monkeys[monkey.throwTarget(item)].items.push_back(item);
            }
            monkey.items.clear();
        }
    }

    ranges::partial_sort(monkeys, std::next(std::begin(monkeys), 2), ranges::greater{}, &Monkey::inspected);

    return monkeys[0].inspected * monkeys[1].inspected;
}

}

template <>
Result exercise<2022, 11, 1>(std::istream& stream)
{
    return exercise(stream, 20u, 3u);
}

template <>
Result exercise<2022, 11, 2>(std::istream& stream)
{
    return exercise(stream, 10'000u, 1u);
}

}
