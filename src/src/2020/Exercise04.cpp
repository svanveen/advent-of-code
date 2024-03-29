#include <array>
#include <string>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

static const std::map<std::string, std::regex> keyMap = {
        {"byr", std::regex{R"(^(19[2-9][0-9]|200[0-2])$)"}},
        {"iyr", std::regex{R"(^(201[0-9]|2020)$)"}},
        {"eyr", std::regex{R"(^(202[0-9]|2030)$)"}},
        {"hgt", std::regex{R"(^(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in)$)"}},
        {"hcl", std::regex{R"(^#[0-9a-f]{6}$)"}},
        {"ecl", std::regex{R"(^(amb|blu|brn|gry|grn|hzl|oth)$)"}},
        {"pid", std::regex{R"(^\d{9}$)"}}
};

const auto containsAllKeys = [](auto&& passportEntries)
{
    return ranges::all_of(keyMap | ranges::views::keys, [&](auto&& key) {
        return ranges::count(passportEntries | ranges::views::keys, key) == 1;
    });
};

auto splitEntries(const std::string& str)
{
    return str | ranges::views::tokenize(std::regex{R"([^ ]*)"}, 0, std::regex_constants::match_not_null);
}

auto splitKeyValue(const std::string& str)
{
    static const std::regex regex{R"(([^:]+):([^:]+))"};
    std::smatch match;
    std::regex_match(str, match, regex);
    return std::pair{match[1].str(), match[2].str()};
}

template <typename FILTER>
auto exercise(std::istream& stream, FILTER&& filter)
{
    auto lines = ranges::getlines(stream) | ranges::to_vector;
    auto passports = lines
            | ranges::views::split_when([](auto&& line) { return line.empty(); })
            | ranges::views::transform([](auto&& passportLines)
                {
                    return passportLines
                           | ranges::views::transform(splitEntries)
                           | ranges::views::join
                           | ranges::views::transform(splitKeyValue);
                })
            | ranges::views::filter(filter);

    return ranges::distance(passports);
}

}

template <>
Result exercise<2020, 4, 1>(std::istream& stream)
{
    return exercise(stream, containsAllKeys);
}

template <>
Result exercise<2020, 4, 2>(std::istream& stream)
{
    return exercise(stream, [](auto&& passportEntries)
    {
        return containsAllKeys(passportEntries) && ranges::all_of(passportEntries, [&](auto&& entry)
        {
            return entry.first == "cid" || std::regex_search(entry.second, keyMap.at(entry.first));
        });
    });
}

}
