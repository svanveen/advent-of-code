#ifndef ADVENTOFCODE_POSITION_H
#define ADVENTOFCODE_POSITION_H

namespace aoc::utils
{

namespace detail
{

template <std::size_t N, typename ARG0, typename ...ARGS, std::size_t ...INDICES>
auto toArray(const std::tuple<ARG0, ARGS...>& tuple, std::index_sequence<INDICES...>)
{
    static_assert(1 + sizeof...(ARGS) <= N);
    return std::array<ARG0, N>{std::get<INDICES>(tuple)...};
}

}

template <std::size_t N, typename ARG0, typename ...ARGS>
auto toArray(const std::tuple<ARG0, ARGS...>& tuple)
{
    return detail::toArray<N>(tuple, std::index_sequence_for<ARG0, ARGS...>{});
}

template <typename T, std::size_t DIMS>
struct Position
{
    Position() = default;
    constexpr Position(const std::array<T, DIMS>& dims)
        : dims(dims)
    {}

    T& operator[](std::size_t dim) { return dims[dim]; }
    const T& operator[](std::size_t dim) const { return dims[dim]; }

    template <typename ...ARGS>
    static Position create(const std::tuple<ARGS...>& tuple)
    {
        return toArray<DIMS>(tuple);
    }

    bool operator==(const Position& other) const { return dims == other.dims; }
    bool operator!=(const Position& other) const { return dims != other.dims; }
    bool operator<=(const Position& other) const { return (*this < other) || (*this == other); }
    bool operator>=(const Position& other) const { return (*this > other) || (*this == other); }
    bool operator>(const Position& other) const  { return other < *this; }
    bool operator<(const Position& other) const
    {
        for (int i = 0; i < DIMS; ++i)
        {
            if (dims[i] < other.dims[i])
            {
                return true;
            }
            if (dims[i] > other.dims[i])
            {
                return false;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Position& position)
    {
        stream << '[';
        std::copy(std::begin(position.dims), std::end(position.dims), std::ostream_iterator<int>{stream, ","});
        return stream << ']';
    }

    std::array<T, DIMS> dims;
};

template <typename T, std::size_t DIMS>
struct Direction
{
    Direction() = default;
    constexpr Direction(const std::array<T, DIMS>& dims)
        : dims(dims)
    {}

    T& operator[](std::size_t dim) { return dims[dim]; }
    const T& operator[](std::size_t dim) const { return dims[dim]; }

    template <typename ...ARGS>
    static Direction create(const std::tuple<ARGS...>& tuple)
    {
        return toArray<DIMS>(tuple);
    }

    bool operator==(const Direction& other) const { return dims == other.dims; }
    bool operator!=(const Direction& other) const { return dims != other.dims; }

    friend std::ostream& operator<<(std::ostream& stream, const Direction& direction)
    {
        stream << '[';
        std::copy(std::begin(direction.dims), std::end(direction.dims), std::ostream_iterator<int>{stream, ","});
        return stream << ']';
    }

    std::array<T, DIMS> dims;
};

template <typename T, std::size_t DIMS>
Direction<T, DIMS> operator-(const Position<T, DIMS>& lhs, const Position<T, DIMS>& rhs)
{
    return toArray<DIMS>(ranges::tuple_transform(lhs.dims, rhs.dims, std::minus<>{}));
}

template <typename T, std::size_t DIMS>
Position<T, DIMS> operator+(const Position<T, DIMS>& position, const Direction<T, DIMS>& direction)
{
    return toArray<DIMS>(ranges::tuple_transform(position.dims, direction.dims, std::plus<>{}));
}

template <typename T, std::size_t DIMS>
Position<T, DIMS>& operator+=(Position<T, DIMS>& position, const Direction<T, DIMS>& direction)
{
    position = position + direction;
    return position;
}

template <typename T, std::size_t DIMS>
Direction<T, DIMS> operator+(const Direction<T, DIMS>& lhs, const Direction<T, DIMS>& rhs)
{
    return toArray<DIMS>(ranges::tuple_transform(lhs.dims, rhs.dims, std::plus<>{}));
}

template <typename T, std::size_t DIMS>
Direction<T, DIMS>& operator+=(Direction<T, DIMS>& lhs, const Direction<T, DIMS>& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T, std::size_t DIMS>
Direction<T, DIMS> operator*(T scale, const Direction<T, DIMS>& direction)
{
    return toArray<DIMS>(ranges::tuple_transform(direction.dims, ranges::bind_back(std::multiplies<>{}, scale)));
}

}

#endif //ADVENTOFCODE_POSITION_H
