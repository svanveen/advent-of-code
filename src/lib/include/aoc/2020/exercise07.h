#ifndef ADVENT_OF_CODE_2020_EXERCISE07_H
#define ADVENT_OF_CODE_2020_EXERCISE07_H

#include <array>
#include <fstream>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view.hpp>

namespace event2020::exercise7
{

namespace impl
{

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

auto exercise(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(parseRule)
        | ranges::views::join
        | ranges::to_vector;
}

}

std::size_t part1(std::istream& stream)
{
    auto rules = impl::exercise(stream);

    auto findContainerBags = [&](auto&& bag)
    {
        return rules
               | ranges::views::filter([&](auto&& rule) { return rule.second.second == bag; })
               | ranges::views::keys;
    };

    auto result = std::vector<std::string>{"shiny gold"};

    while (true)
    {
        auto containing = result
            | ranges::views::transform(findContainerBags)
            | ranges::views::join
            | ranges::to_vector
            | ranges::actions::sort
            | ranges::actions::unique;
        if (ranges::empty(ranges::views::set_difference(containing, result)))
        {
            break;
        }
        result = ranges::views::set_union(result, containing) | ranges::to_vector;
    }

    return result.size() - 1; // remove shiny gold itself from result
}

std::size_t part2(std::istream& stream)
{
    return 0;
}

}


#endif //ADVENT_OF_CODE_2020_EXERCISE07_H
