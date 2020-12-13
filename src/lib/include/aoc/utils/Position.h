#ifndef ADVENTOFCODE_POINT_H
#define ADVENTOFCODE_POINT_H

namespace aoc::utils
{

template <typename INT = int>
struct Position
{
    INT x;
    INT y;

    friend std::ostream& operator<<(std::ostream& stream, const Position& position)
    {
        return stream << '[' << position.x << ',' << position.y << ']';
    }
};

template <typename INT = int>
struct Direction
{
    int dx;
    int dy;

    bool operator==(const Direction& other) const { return dx == other.dx && dy == other.dy; }
    bool operator!=(const Direction& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& stream, const Direction& direction)
    {
        return stream << '[' << direction.x << ',' << direction.y << ']';
    }
};

template <typename INT>
Position<INT> operator+(const Position<INT>& position, const Direction<INT>& direction)
{
    return {position.x + direction.dx, position.y + direction.dy};
}

template <typename INT>
Position<INT>& operator+=(Position<INT>& position, const Direction<INT>& direction)
{
    position = position + direction;
    return position;
}

template <typename INT>
Direction<INT> operator+(const Direction<INT>& lhs, const Direction<INT>& rhs)
{
    return {lhs.dx + rhs.dx, lhs.dy + rhs.dy};
}

template <typename INT>
Direction<INT>& operator+=(Direction<INT>& lhs, const Direction<INT>& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename INT>
Direction<INT> operator*(INT scale, const Direction<INT>& direction)
{
    return {scale * direction.dx, scale * direction.dy};
}

}

#endif //ADVENTOFCODE_POINT_H
