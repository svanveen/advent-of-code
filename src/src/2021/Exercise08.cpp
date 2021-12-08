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

std::string operator-(const std::string& lhs, const std::string& rhs)
{
    return lhs
        | ranges::views::filter([&](char c) { return rhs.find(c) == std::string::npos; })
        | ranges::to<std::string>;
}

struct Note
{
    static Note parse(const std::string& str)
    {
        const auto regex = std::regex{R"([a-g]+)"};

        const auto tokens = str | ranges::views::tokenize(regex);

        auto result = Note{};
        ranges::copy(tokens | ranges::views::take(10), result.signalPatterns.begin());
        ranges::sort(result.signalPatterns, ranges::less{}, [](auto &&str) { return str.size(); });
        ranges::copy(tokens | ranges::views::drop(10), result.outputValue.begin());
        return result;
    }

    int computeValue() const
    {
        auto segments = std::array<std::string, 10>{};
        segments[1] = signalPatterns[0];
        segments[7] = signalPatterns[1];
        segments[4] = signalPatterns[2];
        segments[8] = signalPatterns[9];

        const auto top = segments[7] - segments[1];
        assert(top.size() == 1);
        const auto bottomLeftCorner = segments[8] - (segments[4] + top);
        assert(bottomLeftCorner.size() == 2);

        auto bottom = std::string{};
        auto topLeft = std::string{};
        {
            const auto nineNoBottom = segments[4] + top;
            const auto zeroNoTopLeft = segments[7] + bottomLeftCorner;
            for (auto i = 6; i < 9; ++i) // all digits with one segment missing
            {
                assert(signalPatterns[i].size() == 6);
                if (auto tmp = signalPatterns[i] - zeroNoTopLeft; tmp.size() == 1)
                {
                    topLeft = std::move(tmp);
                    segments[0] = signalPatterns[i];
                }
                else if (auto tmp2 = signalPatterns[i] - nineNoBottom; tmp2.size() == 1)
                {
                    bottom = std::move(tmp2);
                    segments[9] = signalPatterns[i];
                }
                else
                {
                    segments[6] = signalPatterns[i];
                }
            }
        }
        assert(!segments[0].empty() && !segments[6].empty() && !segments[9].empty());
        assert(bottom.size() == 1 && topLeft.size() == 1);

        const auto center = segments[8] - segments[0];
        assert(center.size() == 1);
        segments[3] = segments[1] + top + center + bottom;

        for (auto i = 3; i < 6; ++i)
        {
            if (ranges::is_permutation(signalPatterns[i], segments[3]))
            {
                segments[3] = signalPatterns[i];
            }
            else if (const auto tmp = segments[6] - signalPatterns[i]; tmp.size() == 1)
            {
                segments[5] = signalPatterns[i];
            }
            else
            {
                segments[2] = signalPatterns[i];
            }
        }
        assert(!segments[2].empty() && !segments[5].empty());

        auto result = int{};
        for (auto i = 0; i < 4; ++i)
        {
            const auto number = ranges::distance
            (
                ranges::begin(segments),
                ranges::find_if(segments, [&](auto&& str)
                {
                    return ranges::is_permutation(str, outputValue[i]);
                })
            );
            result += std::pow(10, 3 - i) * number;
        }

        return result;
    }

    std::array<std::string, 10> signalPatterns;
    std::array<std::string, 4> outputValue;
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
                const auto size = str.size();
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
