#include <optional>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

auto parseConnection(const std::string& str)
{
    auto regex = std::regex{R"((\w+)-(\w+))"};
    auto match = std::smatch{};

    std::regex_match(str, match, regex);

    return ranges::views::concat
    (
        ranges::views::single(std::pair{match[1].str(), match[2].str()}),
        ranges::views::single(std::pair{match[2].str(), match[1].str()})
    );
}

auto parseConnections(std::istream& stream)
{
    return ranges::getlines(stream)
       | ranges::views::transform(parseConnection)
       | ranges::views::join
       | ranges::to<std::unordered_multimap>;
}

std::size_t countPaths(const std::unordered_multimap<std::string, std::string>& connections, std::unordered_map<std::string, bool>& visited, std::optional<std::string>& twice, bool singleSmallAllowedTwice, const std::string& current = "start")
{
    if (current == "start" && visited[current])
    {
        return 0;
    }
    if (current == "end")
    {
        return 1;
    }

    if ((current[0] >= 'a' && current[0] <= 'z') && visited[current])
    {
        if (!singleSmallAllowedTwice || twice)
        {
            return 0;
        }
        twice = current;
    }

    visited[current] = true;

    auto paths = std::size_t{0};

    const auto[start, end] = connections.equal_range(current);
    for (auto it = start; it != end; ++it)
    {
        paths += countPaths(connections, visited, twice, singleSmallAllowedTwice, it->second);
    }

    if (twice == current)
    {
        twice.reset();
    }
    else
    {
        visited[current] = false;
    }

    return paths;
}

std::size_t countPaths(std::istream& stream, bool singleSmallAllowedTwice)
{
    const auto connections = parseConnections(stream);
    auto twice = std::optional<std::string>{};
    auto visited = std::unordered_map<std::string, bool>{};

    return countPaths(connections, visited, twice, singleSmallAllowedTwice);
}

}

template <>
Result exercise<2021, 12, 1>(std::istream& stream)
{
    return countPaths(stream, false);
}

template <>
Result exercise<2021, 12, 2>(std::istream& stream)
{
    return countPaths(stream, true);
}

}
