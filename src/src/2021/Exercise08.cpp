#include <bitset>
#include <cassert>
#include <regex>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

using Digit = std::bitset<7>;

Digit parseDigit(const std::string& str)
{
    auto digit = Digit{};
    for (const auto c : str)
    {
        digit.set(c - 'a');
    }
    return digit;
}

struct Note
{
    static Note parse(const std::string& str)
    {
        const auto regex = std::regex{R"([a-g]+)"};

        const auto tokens = str
            | ranges::views::tokenize(regex)
            | ranges::views::transform(parseDigit);

        auto result = Note{};
        ranges::copy(tokens | ranges::views::take(10), result.signalPatterns.begin());
        ranges::sort(result.signalPatterns, ranges::less{}, [](auto&& digit) { return digit.count(); });
        ranges::copy(tokens | ranges::views::drop(10), result.outputValue.begin());
        return result;
    }

    int computeValue() const
    {
        auto segments = std::array<Digit, 10>{};
        segments[1] = signalPatterns[0];
        segments[7] = signalPatterns[1];
        segments[4] = signalPatterns[2];
        segments[8] = signalPatterns[9];

        for (auto i = 3; i < 6; ++i)
        {
            if ((signalPatterns[i] & segments[1]).count() == 2)
            {
                segments[3] = signalPatterns[i];
                break;
            }
        }
        assert(segments[3].any());

        for (auto i = 6; i < 9; ++i)
        {
            if ((signalPatterns[i] & segments[1]).count() == 2 && (signalPatterns[i] & ~segments[3]).count() == 2)
            {
                segments[0] = signalPatterns[i];
            }
            else if ((signalPatterns[i] & segments[1]).count() == 2)
            {
                segments[9] = signalPatterns[i];
            }
            else
            {
                segments[6] = signalPatterns[i];
            }
        }
        assert(segments[0].any());
        assert(segments[6].any());
        assert(segments[9].any());

        for (auto i = 3; i < 6; ++i)
        {
            if (signalPatterns[i] == segments[3])
            {
                // noop
            }
            else if ((segments[6] & ~signalPatterns[i]).count() == 1)
            {
                segments[5] = signalPatterns[i];
            }
            else
            {
                segments[2] = signalPatterns[i];
            }
        }
        assert(segments[2].any());
        assert(segments[5].any());

        auto result = int{};

        for (auto i = 0; i < 4; ++i)
        {
            result += std::pow(10, 3 - i) * ranges::distance(ranges::begin(segments), ranges::find(segments, outputValue[i]));
        }

        return result;
    }

    std::array<Digit, 10> signalPatterns;
    std::array<Digit, 4> outputValue;
};

}

template <>
Result exercise<2021, 8, 1>(std::istream& stream)
{
    const auto notes = ranges::getlines(stream)
        | ranges::views::transform(Note::parse)
        | ranges::to_vector;

    return ranges::distance
    (
        notes
            | ranges::views::transform([](auto&& note) { return note.outputValue | ranges::views::all; })
            | ranges::views::join
            | ranges::views::filter([](auto&& str)
            {
                const auto size = str.count();
                return (size == 2) || (size == 3) || (size == 4) || (size == 7);
            })
    );
}

template <>
Result exercise<2021, 8, 2>(std::istream& stream)
{
    auto notes = ranges::getlines(stream)
       | ranges::views::transform(Note::parse)
       | ranges::to_vector;

    return ranges::accumulate(notes, 0, ranges::plus{}, [](auto&& note)
    {
        return note.computeValue();
    });
}

}
