#include <regex>
#include <string>
#include <variant>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

namespace
{

struct CharacterRule
{
    char character;
};

using RuleReference = std::vector<std::size_t>;

struct ReferenceRule
{
    std::vector<RuleReference> ruleReferencesAlternatives;
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

class RuleSet
{
public:
    template <typename It>
    RuleSet(It from, It to)
        : rules(from, to)
    {}

    bool operator()(const std::string& str) const
    {
        const auto [matched, remainder] = matches(std::string_view{str}, rules.at(0));
        return matched && remainder.empty();
    }

private:
    std::pair<bool, std::string_view> matches(std::string_view str, Rule rule) const
    {
        return std::visit([&](auto&& rule) { return matches(str, rule); }, rule);
    }

    std::pair<bool, std::string_view> matches(std::string_view str, CharacterRule rule) const
    {
        if (str.empty())
        {
            return {false, {}};
        }
        return {str.front() == rule.character, str.substr(1)};
    }

    std::pair<bool, std::string_view> matches(std::string_view str, ReferenceRule rule) const
    {
        for (auto&& ruleReferences : rule.ruleReferencesAlternatives)
        {
            auto remainder = str;
            auto matched = ranges::all_of(ruleReferences, [&](auto&& ruleReference)
            {
                auto [matched, rem] = matches(remainder, rules.at(ruleReference));
                remainder = rem;
                return matched;
            });
            if (matched)
            {
                return {matched, remainder};
            }
        };
        return {false, {}};
    }

private:
    std::map<std::size_t, Rule> rules;
};

}

template <>
std::size_t exercise<2020, 19, 1>(std::istream& stream)
{
    auto blocks = ranges::getlines(stream)
        | ranges::views::split("");

    auto rules = (*blocks.begin())
        | ranges::views::transform(parseRule)
        | ranges::to_vector; // TODO: Remove to_vector

    auto ruleset = RuleSet{std::begin(rules), std::end(rules)};

    auto messages = (*++blocks.begin()) | ranges::to_vector;

    return ranges::distance(messages | ranges::views::filter(ruleset));
}

template <>
std::size_t exercise<2020, 19, 2>(std::istream& stream)
{
    return 0;
}

}
