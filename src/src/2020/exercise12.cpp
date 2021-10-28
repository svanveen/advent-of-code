#include <map>
#include <string>
#include <variant>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = aoc::utils::Position<int, 2>;
using Direction = aoc::utils::Direction<int, 2>;

enum class CardinalDirection
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum class Turn
{
    LEFT,
    RIGHT
};

struct Forward {};

static const std::map<CardinalDirection, Direction> directionMap
{
    {CardinalDirection::NORTH, {{0, 1}}},
    {CardinalDirection::EAST,  {{1, 0}}},
    {CardinalDirection::SOUTH, {{0, -1}}},
    {CardinalDirection::WEST,  {{-1, 0}}},
};

CardinalDirection turnCardinalDirection(CardinalDirection direction, Turn turn, int value)
{
    const auto step = (turn == Turn::RIGHT ? value : (360 - value)) / 90;
    return static_cast<CardinalDirection>((static_cast<int>(direction) + step) % 4);
}

struct Instruction
{
    using Code = std::variant<CardinalDirection, Turn, Forward>;
    Code code;
    int value;

    static Instruction parse(const std::string& str)
    {
        std::smatch match;
        std::regex_match(str, match, std::regex{R"(([NESWFLR])(\d+))"});

        const auto value = std::stoi(match[2]);
        switch (*match[1].first)
        {
            case 'N': return {CardinalDirection::NORTH, value};
            case 'E': return {CardinalDirection::EAST, value};
            case 'S': return {CardinalDirection::SOUTH, value};
            case 'W': return {CardinalDirection::WEST, value};
            case 'L': return {Turn::LEFT, value};
            case 'R': return {Turn::RIGHT, value};
            case 'F': return {Forward{}, value};
        }
        throw std::runtime_error{"could not parse instruction"};
    }
};

class AbstractFerry
{
protected:
    virtual void exec(CardinalDirection cardinalDirection, int value) = 0;
    virtual void exec(Turn turn, int value) = 0;
    virtual void exec(Forward, int value) = 0;

public:
    void operator()(const Instruction& instruction)
    {
        std::visit([&, value = instruction.value](auto&& instruction)
        {
            exec(instruction, value);
        }, instruction.code);
    }

    const Position& getPosition() const
    {
        return _position;
    }

protected:
    Position _position = {{}};
};


class Ferry : public AbstractFerry
{
private:
    void exec(CardinalDirection cardinalDirection, int value) override
    {
        _position += value * directionMap.at(cardinalDirection);
    }

    void exec(Turn turn, int value) override
    {
        _direction = turnCardinalDirection(_direction, turn, value);
    }

    void exec(Forward, int value) override
    {
        exec(_direction, value);
    }

private:
    CardinalDirection _direction = CardinalDirection::EAST;
};

class Ferry2 : public AbstractFerry
{
private:
    void exec(CardinalDirection cardinalDirection, int value) override
    {
        _waypoint += value * directionMap.at(cardinalDirection);
    }

    void exec(Turn turn, int value) override
    {
        _waypoint = _waypoint[0] * directionMap.at(turnCardinalDirection(CardinalDirection::EAST, turn, value))
                  + _waypoint[1] * directionMap.at(turnCardinalDirection(CardinalDirection::NORTH, turn, value));
    }

    void exec(Forward, int value) override
    {
        _position += value * _waypoint;
    }

private:
    Direction _waypoint = {{10, 1}};
};

template <typename FERRY>
auto exercise(std::istream& stream)
{
    auto instructions = ranges::getlines(stream)
        | ranges::views::transform(Instruction::parse);
    FERRY ferry{};

    for (auto&& instruction : instructions)
    {
        ferry(instruction);
    }

    const auto& position = ferry.getPosition();
    return std::abs(position[0]) + std::abs(position[1]);
}

}

template <>
Result exercise<2020, 12, 1>(std::istream& stream)
{
    return exercise<Ferry>(stream);
}

template <>
Result exercise<2020, 12, 2>(std::istream& stream)
{
    return exercise<Ferry2>(stream);
}

}
