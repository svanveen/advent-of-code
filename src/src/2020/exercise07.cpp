#include <string>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct ContainingBagCounter
{
    std::size_t operator()(const std::vector<std::string>& bags)
    {
        auto findContainerBags = [&](auto&& bag)
        {
            return rules
                   | ranges::views::filter([&](auto&& rule) { return rule.second.second == bag; })
                   | ranges::views::keys;
        };

        auto containing = bags
            | ranges::views::transform(findContainerBags)
            | ranges::views::join
            | ranges::to_vector
            | ranges::actions::sort
            | ranges::actions::unique;

        if (ranges::empty(ranges::views::set_difference(containing, bags)))
        {
            return bags.size() - 1;
        }
        else
        {
            return (*this)(ranges::views::set_union(bags, containing) | ranges::to_vector);
        }
    }

    std::size_t operator()(const std::string& bag)
    {
        return (*this)(std::vector{bag});
    }

    std::vector<std::pair<std::string, std::pair<int, std::string>>> rules;
};

struct ContainedBagCounter
{
    std::size_t operator()(const std::vector<std::string>& bags)
    {
        auto containedBags = [&](auto&& bag)
        {
            return rules
                   | ranges::views::filter([&](auto&& rule) { return rule.first == bag; })
                   | ranges::views::values
                   | ranges::views::transform([](auto&& contained) { return ranges::views::repeat_n(contained.second, contained.first); })
                   | ranges::views::join;
        };

        auto contained = bags
            | ranges::views::transform(containedBags)
            | ranges::views::join;

        const auto size = ranges::distance(contained);
        if (size > 0)
        {
            return size + (*this)(contained | ranges::to_vector);
        }
        else
        {
            return size;
        }
    }

    std::size_t operator()(const std::string& bag)
    {
        return (*this)(std::vector{bag});
    }

    std::vector<std::pair<std::string, std::pair<int, std::string>>> rules;
};

auto parseRule(const std::string& str)
{
    std::smatch match;
    std::regex_match(str, match, std::regex{R"((\w+ \w+) bags contain (.*)\.)"});

    return ranges::make_iterator_range(match[2].first, match[2].second)
        | ranges::views::tokenize(std::regex{R"((\d) (\w+ \w+) bags?)"}, {1, 2})
        | ranges::views::chunk(2)
        | ranges::views::transform(ranges::to_vector)
        | ranges::views::transform([outter = match[1]](auto&& inner) { return std::pair(outter.str(), std::pair(std::stoi(inner[0]), inner[1].str())); });
}

template <typename COUNTER>
auto exercise(std::istream& stream)
{
    auto rules = ranges::getlines(stream)
           | ranges::views::transform(parseRule)
           | ranges::views::join
           | ranges::to_vector;

    COUNTER counter{std::move(rules)};

    return counter("shiny gold");
}

}

template <>
std::size_t exercise<2020, 7, 1>(std::istream& stream)
{
    return exercise<ContainingBagCounter>(stream);
}

template <>
std::size_t exercise<2020, 7, 2>(std::istream& stream)
{
    return exercise<ContainedBagCounter>(stream);
}

}
