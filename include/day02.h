#ifndef ADVENT_OF_CODE_DAY02_H
#define ADVENT_OF_CODE_DAY02_H

#include <fstream>
#include <regex>
#include <string>
#include <range/v3/view.hpp>

namespace day2
{

namespace impl
{

struct Match
{
    int from;
    int to;
    char character;
    std::string password;
};

auto match(const std::string& str)
{
    static const auto regex = std::regex{R"((\d+)-(\d+) (\w): (\w+))"};
    std::smatch match;
    std::regex_match(str, match, regex);
    return Match{std::stoi(match[1]), std::stoi(match[2]), *match[3].first, match[4]};
}

template <typename FILTER>
auto exercise(const std::string& path, FILTER&& filter)
{
    std::ifstream stream{path + "/2.dat"};
    auto solutions = ranges::getlines(stream)
           | ranges::views::transform(match)
           | ranges::views::filter(filter);

    return ranges::distance(solutions);
}

}

auto exercise1(const std::string& path)
{
    return impl::exercise(path, [](auto&& match)
    {
        const auto count = std::count(std::begin(match.password), std::end(match.password), match.character);
        return (match.from <= count) && (match.to >= count);
    });
}

auto exercise2(const std::string& path)
{
    return impl::exercise(path, [](auto&& match)
    {
        return (match.password[match.from - 1] == match.character) ^ (match.password[match.to - 1] == match.character);
    });
}

}


#endif //ADVENT_OF_CODE_DAY02_H
