#include <regex>
#include <stdexcept>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Position
{
    int x = 0;
    int y = 0;
};

struct AimedPosition : Position
{
    int aim = 0;
};

struct Movement
{
    enum class Direction
    {
        FORWARD,
        DOWN,
        UP
    };

    Direction direction;
    int steps;
};

Position operator+(const Position& position, const Movement& movement)
{
    switch (movement.direction)
    {
        case Movement::Direction::FORWARD:
            return {position.x + movement.steps, position.y};
        case Movement::Direction::DOWN:
            return {position.x, position.y + movement.steps};
        case Movement::Direction::UP:
            return {position.x, position.y - movement.steps};
    }
    throw std::logic_error{"invalid direction"};
}

AimedPosition operator+(const AimedPosition& position, const Movement& movement)
{
    switch (movement.direction)
    {
        case Movement::Direction::FORWARD:
            return {position.x + movement.steps, position.y + position.aim * movement.steps, position.aim};
        case Movement::Direction::DOWN:
            return {position.x, position.y, position.aim + movement.steps};
        case Movement::Direction::UP:
            return {position.x, position.y, position.aim - movement.steps};
    }
    throw std::logic_error{"invalid direction"};
}

Movement parseOperation(const std::string& str)
{
    auto regex = std::regex{R"((forward|down|up) (\d+))"};
    auto match = std::smatch{};

    std::regex_match(str, match, regex);

    const auto steps = std::stoi(match[2].str());

    const auto directionMap = std::unordered_map<std::string, Movement::Direction>
    {
        {"forward", Movement::Direction::FORWARD},
        {"down",    Movement::Direction::DOWN},
        {"up",      Movement::Direction::UP},
    };

    return {directionMap.at(match[1]), steps};
}

auto getMovements(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(parseOperation);
}

template <typename POSITION>
Result exercise(std::istream& stream)
{
    const auto finalPosition = ranges::accumulate(getMovements(stream), POSITION{});
    return finalPosition.x * finalPosition.y;
}

}

template <>
Result exercise<2021, 2, 1>(std::istream& stream)
{
    return exercise<Position>(stream);
}

template <>
Result exercise<2021, 2, 2>(std::istream& stream)
{
    return exercise<AimedPosition>(stream);
}

}
