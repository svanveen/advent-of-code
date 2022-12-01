#include <bitset>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/ToInts.h>

using namespace std::literals;

namespace aoc
{

namespace
{

const auto parseNumbers = ranges::views::tokenize(std::regex{R"(\d+)"})
    | utils::toInts<int>;

Result exercise(std::istream& stream, bool exitOnFirst)
{
    auto lines = ranges::getlines(stream);

    auto numbers = (*ranges::begin(lines)) | parseNumbers;

    auto bingos = lines
        | ranges::views::drop(2)
        | ranges::views::split(""s)
        | ranges::views::transform([](auto&& block)
            {
                return block
                    | ranges::views::transform(parseNumbers)
                    | ranges::views::join
                    | ranges::to_vector;
            })
        | ranges::to_vector;

    for (const auto number : numbers)
    {
        for (auto it = bingos.begin(); it != bingos.end();)
        {
            auto& bingo = *it;
            auto cols = std::bitset<5>{}.set();
            auto rows = std::bitset<5>{}.set();
            for (int i = 0; i < 25; ++i)
            {
                if (bingo[i] == number)
                {
                    bingo[i] = -1;
                }
                if  (bingo[i] >= 0)
                {
                    rows[i / 5] = false;
                    cols[i % 5] = false;
                }
            }
            if (cols.any() || rows.any())
            {
                if (exitOnFirst || bingos.size() == 1)
                {
                    return number * ranges::accumulate(bingo, 0, ranges::plus{}, [](auto x) { return x > 0 ? x : 0;});
                }
                it = bingos.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    return 0;
}

}

template <>
Result exercise<2021, 4, 1>(std::istream& stream)
{
    return exercise(stream, true);
}

template <>
Result exercise<2021, 4, 2>(std::istream& stream)
{
    return exercise(stream, false);
}

}
