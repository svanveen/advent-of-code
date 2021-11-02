#include <regex>
#include <string>
#include <variant>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

namespace
{

struct CharacterRule
{
    char character;
};

using RuleReferences = std::vector<std::size_t>;

struct ReferenceRule
{
    std::vector<RuleReferences> ruleReferencesAlternatives;
};

using Rule = std::variant<CharacterRule, ReferenceRule>;

std::pair<std::size_t, Rule> parseRule(const std::string& str)
{
    {
        static const std::regex regex{R"((\d+): \"(\w)\")"};
        std::smatch match;
        if (std::regex_match(str, match, regex))
        {
            return {std::stoull(match[1]), CharacterRule{*match[2].first}};
        }
    }
    {
        static const std::regex regex{R"((\d+): (\d+( \d+)*( \| \d+( \d+)*)*))"};
        std::smatch match;
        if (std::regex_match(str, match, regex))
        {
            auto ruleReferences = ranges::make_iterator_range(match[2].first, match[2].second)
                | ranges::views::tokenize(std::regex{R"([|])"}, -1)
                | ranges::views::transform([](auto&& submatch)
                    {
                        return ranges::make_iterator_range(submatch.first, submatch.second)
                            | ranges::views::tokenize(std::regex{R"(\d+)"})
                            | ranges::views::transform([](auto&& number) { return std::stoull(number); })
                            | ranges::to_vector;
                    })
                | ranges::to_vector;
            return {std::stoull(match[1]), ReferenceRule{ruleReferences}};
        }
    }
    throw std::runtime_error{"parsing error"};
}

struct RuleSet
{
    using Matches = std::vector<std::string_view>;
public:
    template <typename It>
    RuleSet(It from, It to)
        : rules(from, to)
    {}

    bool operator()(const std::string& str) const
    {
        const auto results = matches(std::string_view{str}, rules.at(0));
        return !ranges::empty(results | ranges::views::filter([](auto&& m) { return m.empty(); }));
    }

    Matches matches(std::string_view str, Rule rule) const
    {
        return std::visit([&](auto&& rule) { return matches(str, rule); }, rule);
    }

    Matches matches(std::string_view str, CharacterRule rule) const
    {
        if (str.empty() || (str.front() != rule.character))
        {
            return {};
        }
        return {{str.substr(1)}};
    }

    Matches matches(std::string_view str, ReferenceRule rule) const
    {
        return rule.ruleReferencesAlternatives
            | ranges::views::transform([&](auto&& ruleReferences) { return matches(str, ruleReferences); })
            | ranges::actions::join;
    }

    Matches matches(std::string_view str, RuleReferences ruleReferences) const
    {
        auto remainders = std::vector<std::string_view>{str};
        for (auto&& ruleReference : ruleReferences)
        {
            remainders = remainders
                | ranges::views::transform([&](auto&& remainder) { return matches(remainder, rules.at(ruleReference)); })
                | ranges::actions::join;
        }
        return remainders;
    }

    std::map<std::size_t, Rule> rules;
};

auto parseInput(std::istream& stream)
{
    auto blocks = ranges::getlines(stream)
        | ranges::views::split("");

    auto rules = (*blocks.begin())
        | ranges::views::transform(parseRule)
        | ranges::views::common;

    auto ruleset = RuleSet{rules.begin(), rules.end()};

    auto messages = (*++blocks.begin());
    return std::pair{std::move(ruleset), messages | ranges::to_vector};
}

}

template <>
Result exercise<2020, 19, 1>(std::istream& stream)
{
    const auto[ruleset, messages] = parseInput(stream);

    return ranges::distance(messages | ranges::views::filter(ruleset));
}

template <>
Result exercise<2020, 19, 2>(std::istream& stream)
{
    auto[ruleset, messages] = parseInput(stream);

    ruleset.rules[8]  = ReferenceRule{{{42}, {42, 8}}};
    ruleset.rules[11] = ReferenceRule{{{42, 31}, {42, 11, 31}}};

    return ranges::distance(messages | ranges::views::filter(ruleset));
}

}
