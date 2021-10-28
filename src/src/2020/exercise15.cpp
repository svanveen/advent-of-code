#include <map>
#include <string>
#include <aoc/exercises.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

namespace aoc
{

namespace
{

auto exercise(std::istream& stream, std::size_t N)
{
    auto startingNumbers = ranges::getlines(stream, ',')
        | ranges::views::transform([](auto&& number) { return std::stoull(number); })
        | ranges::to_vector;

    auto numberTurnPairs = ranges::views::indices(std::size_t{0}, startingNumbers.size() - 1) // don't fill last one into map yet
        | ranges::views::transform([&](auto&& idx) { return std::pair{startingNumbers[idx], idx + 1}; });
    auto numberTurnMap = std::map<std::size_t, std::size_t>{ranges::begin(numberTurnPairs), ranges::end(numberTurnPairs)};

    auto lastNumber = startingNumbers.back();
    for (auto turn = startingNumbers.size() + 1; turn <= N; ++turn)
    {
        auto& lastNumbersTurn = numberTurnMap[lastNumber];
        lastNumber = (lastNumbersTurn == 0) ? 0 : (turn - 1 - lastNumbersTurn);
        lastNumbersTurn = turn - 1;
    }
    return lastNumber;
}

}

template <>
Result exercise<2020, 15, 1>(std::istream& stream)
{
    return exercise(stream, 2020);
}

template <>
Result exercise<2020, 15, 2>(std::istream& stream)
{
    return exercise(stream, 30000000);
}

}
