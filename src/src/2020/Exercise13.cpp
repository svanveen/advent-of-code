#include <string>
#include <aoc/Exercise.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>

namespace aoc
{

namespace
{

struct BusId
{
    long long int value = 0;
    long long int offset = 0;
};

BusId computeAscendingArrivalTime(BusId idA, BusId idB)
{
    if (idB.value < idA.value)
    {
        std::swap(idA, idB); //ensure idB has the larger value to increase speed
    }
    if (idA.value == 0)
    {
        return idB;
    }
    BusId result;
    for (auto multiple = idB.value; ; multiple += idB.value)
    {
        if ((multiple - idB.offset + idA.offset) % idA.value == 0)
        {
            result.offset = -(multiple - idB.offset);
        }
        if (multiple % idA.value == 0)
        {
            result.value = multiple;
            return result;
        }
    }
}

auto getDepature(std::istream& stream)
{
    std::string line;
    std::getline(stream, line);
    return std::stoi(line);
}

}

template <>
Result exercise<2020, 13, 1>(std::istream& stream)
{
    const auto departure = getDepature(stream);
    auto busIds = ranges::getlines(stream, ',')
        | ranges::views::filter(ranges::bind_back(ranges::not_equal_to{}, "x"))
        | ranges::views::transform([](auto&& line) { return std::stoi(line); });

    auto waitTime = [=](auto&& busId)
    {
        return busId - (departure % busId);
    };

    auto bestBusId = ranges::min(busIds, ranges::less{}, waitTime);

    return bestBusId * waitTime(bestBusId);
}

template <>
Result exercise<2020, 13, 2>(std::istream& stream)
{
    (void) getDepature(stream);
    auto busIds = ranges::getlines(stream, ',')
        | ranges::views::drop_while([](auto&& line) { return line == "x"; }) // remove leading x
        | ranges::to_vector;

    auto idxBusIdPairs = ranges::views::iota(0u, busIds.size())
        | ranges::views::filter([&](auto&& idx) { return busIds[idx] != "x"; })
        | ranges::views::transform([&](auto&& idx) { return BusId{std::stoll(busIds[idx]), static_cast<long long>(idx)}; });

    return -ranges::accumulate(idxBusIdPairs, BusId{}, computeAscendingArrivalTime).offset;
}

}
