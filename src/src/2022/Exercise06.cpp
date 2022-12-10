#include <bitset>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

Result exercise(std::istream& stream, std::size_t sequenceLength)
{
    auto str = std::string{};
    std::getline(stream, str);

    return ranges::distance
    (
        str
            | ranges::views::sliding(sequenceLength)
            | ranges::views::take_while([&](auto&& rng)
            {
                auto bits = std::bitset<26>{};
                for (auto c : rng)
                {
                    bits.set(c - 'a');
                }
                return bits.count() != sequenceLength;
            })
    ) + sequenceLength;
}

}

template <>
Result exercise<2022, 6, 1>(std::istream& stream)
{
    return exercise(stream, 4);
}

template <>
Result exercise<2022, 6, 2>(std::istream& stream)
{
    return exercise(stream, 14);
}

}
