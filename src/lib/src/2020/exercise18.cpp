#include <regex>
#include <string>
#include <variant>
#include <range/v3/algorithm.hpp.>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

using Operation = std::variant<std::plus<>, std::multiplies<>>;

struct OpeningBrace{};
struct ClosingBrace{};

using Token = std::variant<int, Operation, OpeningBrace, ClosingBrace>;

auto parseTokens(const std::string& str)
{
    auto parseToken = [](auto&& part) -> Token
    {
        switch (*part.first)
        {
            case '+': return std::plus<>{};
            case '*': return std::multiplies<>{};
            case '(': return OpeningBrace{};
            case ')': return ClosingBrace{};
            default:  return std::stoi(part);
        }
    };

    auto tokens = str
        | ranges::views::tokenize(std::regex{R"((\d+|[*+()]))"})
        | ranges::views::transform(parseToken);

    return 0;
}

}

template <>
std::size_t exercise<2020, 18, 1>(std::istream& stream)
{
    ranges::getlines(stream)
        | ranges::views::transform(parseTokens);
    return 0;
}

template <>
std::size_t exercise<2020, 18, 2>(std::istream& stream)
{
    return 0;
}

}
