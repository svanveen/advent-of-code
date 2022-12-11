#include <set>
#include <stdexcept>
#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Position.h>

namespace aoc
{

namespace
{

using Position = utils::Position<int, 2>;
using Direction = utils::Direction<int, 2>;

template <std::size_t LENGTH>
struct Rope
{
    void move(const Direction& direction)
    {
        knots.front() += direction;

        for (auto idx : ranges::views::indices(std::size_t{1}, LENGTH))
        {
            const auto dir = knots[idx - 1] - knots[idx];

            if (std::abs(dir[0]) > 1 || (std::abs(dir[0]) == 1 && std::abs(dir[1]) > 1))
            {
                knots[idx][0] += (dir[0] / std::abs(dir[0]));
            }
            if (std::abs(dir[1]) > 1 || (std::abs(dir[1]) == 1 && std::abs(dir[0]) > 1))
            {
                knots[idx][1] += (dir[1] / std::abs(dir[1]));
            }
        }
        tailVisited.insert(knots.back());
    }

    std::array<Position, LENGTH> knots;
    std::set<Position> tailVisited = {Position{{0, 0}}};
};

template <std::size_t ROPE_LENGTH>
Result exercise(std::istream& stream)
{
    auto rope = Rope<ROPE_LENGTH>{};
    for (const auto& line : ranges::getlines(stream))
    {
        const auto direction = [](char c)
        {
            switch (c)
            {
                case 'U': return Direction{{0, 1}};
                case 'D': return Direction{{0, -1}};
                case 'L': return Direction{{-1, 0}};
                case 'R': return Direction{{1, 0}};
                default: throw std::logic_error{"unknown direction"};
            }
        }(line[0]);

        const auto steps = std::atoi(&line[2]);

        for (auto step : ranges::views::indices(steps))
        {
            rope.move(direction);
        }

    }
    return rope.tailVisited.size();
}

}

template <>
Result exercise<2022, 9, 1>(std::istream& stream)
{
    return exercise<2>(stream);
}

template <>
Result exercise<2022, 9, 2>(std::istream& stream)
{
    return exercise<10>(stream);
}

}
