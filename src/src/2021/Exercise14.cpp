#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

class CharacterCounter
{
public:
    explicit CharacterCounter(std::unordered_map<std::string, char> pairInsertions)
        : pairInsertions(std::move(pairInsertions))
        , characterCounts{}
    {}

    std::size_t operator()(const std::string& polymerTemplate, std::size_t iterations)
    {
        count(polymerTemplate, iterations);
        return ranges::max(characterCounts) - ranges::min(characterCounts | ranges::views::filter(ranges::bind_back(ranges::greater{}, 0)));
    }

private:
    void count(const std::string& polymerTemplate, std::size_t iterations)
    {
        for (std::size_t i = 0; i < polymerTemplate.size() - 1; ++i)
        {
            increase(polymerTemplate[i]);
            count(polymerTemplate[i], polymerTemplate[i + 1], iterations);
        }
        increase(polymerTemplate.back());
    }

    void count(char lhs, char rhs, std::size_t iterations)
    {
        if (iterations == 0)
        {
            return;
        }
        if (const auto it = pairInsertions.find(std::string{lhs, rhs}); it != pairInsertions.end())
        {
            increase(it->second);
            count(lhs, it->second, iterations - 1);
            count(it->second, rhs, iterations - 1);
        }
    }

    void increase(char c)
    {
        ++characterCounts[c - 'A'];
    }

private:
    std::unordered_map<std::string, char> pairInsertions;
    std::array<std::size_t, 26> characterCounts;
};

auto parsePairInsertion(const std::string& str)
{
    auto regex = std::regex{R"((\w+) -> (\w))"};
    auto match = std::smatch{};

    std::regex_match(str, match, regex);

    return std::pair{match[1].str(), *match[2].first};
}

auto exercise(std::istream& stream, std::size_t iterations)
{
    auto lines = ranges::getlines(stream);
    auto polymerTemplate = *ranges::begin(lines);
    auto pairInsertions = lines
        | ranges::views::drop(2)
        | ranges::views::transform(parsePairInsertion)
        | ranges::to<std::unordered_map<std::string, char>>;

    auto counter = CharacterCounter{std::move(pairInsertions)};

    return counter(polymerTemplate, iterations);
}

}

template <>
Result exercise<2021, 14, 1>(std::istream& stream)
{
    return exercise(stream, 10);
}

template <>
Result exercise<2021, 14, 2>(std::istream& stream)
{
    return exercise(stream, 40);
}

}
