#include <array>
#include <limits>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

class TemporarySwapper
{
public:
    TemporarySwapper(char& lhs, char& rhs)
        : _lhs(lhs)
        , _rhs(rhs)
    {
        std::swap(_lhs, _rhs);
    }

    ~TemporarySwapper()
    {
        std::swap(_lhs, _rhs);
    }

private:
    char& _lhs;
    char& _rhs;
};

constexpr auto costs = std::array{1, 10, 100, 1000};

constexpr auto isEmpty = [](char c) { return c == '\0'; };

template <std::size_t ROOM_SIZE>
class Burrow
{
public:
    struct Room
    {
        char ampiphod() const
        {
            return 'A' + index;
        }

        bool isOrganized() const
        {
            return ranges::all_of(space, [&](const auto entry)
            {
                return entry == ampiphod();
            });
        }

        std::size_t firstNonEmptyIndex() const
        {
            return *(ranges::views::indices(space.size())
                | ranges::views::filter([&](const auto idx)
                {
                    return space[idx] != '\0';
                })
            ).begin();
        }

        std::size_t lastEmptyIndex() const
        {
            return *(ranges::views::indices(space.size())
                | ranges::views::reverse
                | ranges::views::filter([&](const auto idx)
                {
                    return space[idx] == '\0';
                })
            ).begin();
        }

        bool canMoveFrom() const
        {
            auto nonEmptySpace = space | ranges::views::drop_while(isEmpty);
            if (ranges::empty(nonEmptySpace))
            {
                return false;
            }
            return (*nonEmptySpace.begin() != ampiphod()) || ranges::any_of(nonEmptySpace, [&](const auto c)
            {
                return c != ampiphod();
            });
        };

        bool canMoveTo() const
        {
            auto nonEmptySpace = space | ranges::views::drop_while(isEmpty);
            if (ranges::empty(nonEmptySpace))
            {
                return true;
            }
            return ranges::all_of(nonEmptySpace, [&](const auto c)
            {
                return c == ampiphod();
            });
        };

        char& operator[](std::size_t index)
        {
            return space[index];
        }

        const char& operator[](std::size_t index) const
        {
            return space[index];
        }

        std::size_t index;
        std::array<char, ROOM_SIZE> space;
    };

    Burrow(std::array<Room, 4> rooms)
        : rooms(rooms)
    {}

    bool isOrganized() const
    {
        return ranges::all_of(rooms, [&](const auto& room) { return room.isOrganized(); });
    }

    std::size_t computeEnergyToOrganize() const
    {
        auto copy = *this;
        const auto energy = copy.computeEnergyToOrganizeImpl();
        if (!energy)
        {
            throw std::runtime_error{"could not organize"};
        }
        return *energy;
    }

private:
    static std::size_t index(char amphipod)
    {
        return amphipod - 'A';
    }

    static std::size_t hallwayIndexInFrontOfRoom(std::size_t roomIdx)
    {
        return std::size_t{2} + 2 * roomIdx;
    }

    static std::size_t hallwayIndexInFrontOfRoom(char amphipod)
    {
        return hallwayIndexInFrontOfRoom(index(amphipod));
    }

    Room& room(char amphipod)
    {
        return rooms[index(amphipod)];
    }

    std::optional<std::size_t> computeEnergyToOrganizeImpl()
    {
        if (isOrganized())
        {
            return 0;
        }

        const auto isHallwayEmpty = [&](auto idx) { return isEmpty(hallway[idx]); };
        const auto isNotHallwayInFrontOfAnyRoom = [](auto idx) { return idx < 2 || idx > 8 || ((idx - 2) % 2 != 0); };
        const auto canMoveFromRoom = [&](const auto& room) { return room.canMoveFrom(); };
        const auto canMoveToRoom = [&](const auto& room) { return room.canMoveTo(); };

        auto bestEnergySolution = std::optional<std::size_t>{};
        const auto updateBestEnergySolution = [&](char& from, char& to, size_t steps, char amphipod)
        {
            auto swapper = TemporarySwapper{from, to};
            if (const auto nextEnergy = computeEnergyToOrganizeImpl())
            {
                const auto energy = *nextEnergy + (steps * costs[index(amphipod)]);
                if (!bestEnergySolution || energy < bestEnergySolution)
                {
                    bestEnergySolution = energy;
                }
            }
        };

        for (const auto idx : ranges::views::indices(hallway.size()) | ranges::views::filter(ranges::not_fn(isHallwayEmpty)))
        {
            const auto amphipod = hallway[idx];
            const auto roomHallwayIdx = hallwayIndexInFrontOfRoom(amphipod);
            const auto [from, to] = (idx < roomHallwayIdx) ? std::pair{idx + 1, roomHallwayIdx} : std::pair{roomHallwayIdx, idx - 1};

            if (ranges::all_of(ranges::views::closed_indices(from ,to), isHallwayEmpty))
            {
                auto& destination = room(amphipod);
                if (destination.canMoveTo())
                {
                    const auto roomPosition = destination.firstNonEmptyIndex() - 1;
                    updateBestEnergySolution(hallway[idx], destination[roomPosition], to - from + roomPosition + 2, amphipod);
                }
            }
        }
        if (bestEnergySolution)
        {
            // early exit since moving into house is necessary anyways
            return bestEnergySolution;
        }
        for (auto& room : rooms | ranges::views::filter(canMoveFromRoom))
        {
            const auto roomPosition = room.firstNonEmptyIndex();
            const auto hallwayInFrontOfRoomIdx = hallwayIndexInFrontOfRoom(room.index);
            for (const auto hallwayIdx : ranges::views::indices(std::size_t{0}, hallway.size()) | ranges::views::filter(isNotHallwayInFrontOfAnyRoom))
            {
                const auto [from, to] = (hallwayIdx < hallwayInFrontOfRoomIdx) ? std::pair{hallwayIdx, hallwayInFrontOfRoomIdx} : std::pair{hallwayInFrontOfRoomIdx, hallwayIdx};
                if (ranges::all_of(ranges::views::closed_indices(from, to), isHallwayEmpty))
                {
                    updateBestEnergySolution(room[roomPosition], hallway[hallwayIdx], to - from + roomPosition + 1, room[roomPosition]);
                }
            }
        }
        return bestEnergySolution;
    }

private:
    std::array<Room, 4> rooms;
    std::array<char, 11> hallway = {};
};

}

template <>
Result exercise<2021, 23, 1>(std::istream& stream)
{
    auto lines = ranges::getlines(stream);
    const auto roomUpper = *(lines | ranges::views::drop(2)).begin();
    const auto roomLower = *(lines | ranges::views::drop(1)).begin();

    auto burrow = Burrow<2>
    {
        {
            Burrow<2>::Room{0, {roomUpper[3], roomLower[3]}},
            Burrow<2>::Room{1, {roomUpper[5], roomLower[5]}},
            Burrow<2>::Room{2, {roomUpper[7], roomLower[7]}},
            Burrow<2>::Room{3, {roomUpper[9], roomLower[9]}}
        }
    };
    return burrow.computeEnergyToOrganize();
}

template <>
Result exercise<2021, 23, 2>(std::istream& stream)
{
    auto lines = ranges::getlines(stream);
    const auto roomUpper = *(lines | ranges::views::drop(2)).begin();
    const auto roomLower = *(lines | ranges::views::drop(1)).begin();

    auto burrow = Burrow<4>
    {
        {
            Burrow<4>::Room{0, {roomUpper[3], 'D', 'D', roomLower[3]}},
            Burrow<4>::Room{1, {roomUpper[5], 'C', 'B', roomLower[5]}},
            Burrow<4>::Room{2, {roomUpper[7], 'B', 'A', roomLower[7]}},
            Burrow<4>::Room{3, {roomUpper[9], 'A', 'C', roomLower[9]}}
        }
    };
    return burrow.computeEnergyToOrganize();
}

}
