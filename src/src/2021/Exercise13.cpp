#include <regex>
#include <set>
#include <sstream>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<int, 2>;

Position parsePosition(const std::string& str)
{
    auto regex = std::regex{R"((\d+),(\d+))"};
    auto match = std::smatch{};

    std::regex_match(str, match, regex);

    return {{std::stoi(match[2]), std::stoi(match[1])}};
}

Position parseFold(const std::string& str)
{
    auto regex = std::regex{R"(fold along ([xy])=(\d+))"};
    auto match = std::smatch{};

    std::regex_match(str, match, regex);

    if (*match[1].first == 'x')
    {
        return {{0, std::stoi(match[2])}};
    }
    else
    {
        return {{std::stoi(match[2]), 0}};
    }
}

auto parseInput(std::istream& stream)
{
    auto positions = ranges::getlines(stream)
        | ranges::views::take_while([](const auto& str) { return !str.empty(); })
        | ranges::views::transform(parsePosition)
        | ranges::to<std::set<Position>>;

    auto folds = ranges::getlines(stream)
        | ranges::views::drop_while([](const auto& str) { return str.empty(); })
        | ranges::views::transform(parseFold)
        | ranges::to_vector;
    return std::pair{std::move(positions), std::move(folds)};
}

Position foldPosition(const Position& position, const Position& foldAxis)
{
    if (foldAxis[0] > 0 && position[0] >= foldAxis[0])
    {
        return {{foldAxis[0] - (position[0] - foldAxis[0]), position[1]}};
    }
    if (foldAxis[1] > 0 && position[1] >= foldAxis[1])
    {
        return {{position[0], foldAxis[1] - (position[1] - foldAxis[1])}};
    }
    return position;
}

std::set<Position> fold(const std::set<Position>& positions, const Position& foldAxis)
{
    return positions
        | ranges::views::transform(ranges::bind_back(foldPosition, foldAxis))
        | ranges::to<std::set<Position>>;
}

}

template <>
Result exercise<2021, 13, 1>(std::istream& stream)
{
    const auto [positions, folds] = parseInput(stream);
    return fold(positions, folds.front()).size();
}

template <>
Result exercise<2021, 13, 2>(std::istream& stream)
{
    auto [positions, folds] = parseInput(stream);
    for (const auto& foldAxis : folds)
    {
        positions = fold(positions, foldAxis);
    }

    auto os = std::stringstream{};
    os << '\n';

    auto lastPos = Position{{0, -1}};
    for (const auto& pos : positions)
    {
        if (pos[0] != lastPos[0])
        {
            lastPos = Position{{ pos[0], -1}}; // we assume here that there are no empty lines
            os << '\n';
        }
        for (int i = lastPos[1] + 1; i < pos[1]; ++i)
        {
            os << ' ';
        }
        os << '#';
        lastPos = pos;
    }

    return os.str();
}

}
