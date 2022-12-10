#include <list>
#include <vector>
#include <boost/phoenix/bind.hpp>
#include <boost/spirit/include/qi.hpp>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

using Stacks = std::vector<std::list<char>>;

template <typename CRANE>
Result exercise(std::istream& stream, CRANE&& crane)
{
    using namespace boost::phoenix;
    using namespace boost::spirit;
    auto stacks = Stacks{};

    auto lines = ranges::getlines(stream);
    for (const auto& line : lines)
    {
        auto idx = 0;
        const auto empty = repeat(3)[ascii::space][([&]() { ++idx; } )];
        const auto supply = ('[' >> ascii::upper >> ']')[([&](const auto letter)
        {
            if (idx >= stacks.size())
            {
                stacks.resize(idx + 1);
            }
            stacks[idx].push_front(letter);
            ++idx;
        })];
        auto rule = (empty | supply) % ascii::space;
        if (!qi::parse(line.begin(), line.end(), rule))
        {
            break;
        }
    }

    for (const auto& line : lines | ranges::views::drop(2))
    {
        const auto callCrane = [&](int cnt, int from, int to)
        {
            crane(stacks, cnt, from - 1, to - 1);
        };
        auto rule = ("move " >> int_ >> " from " >> int_ >> " to " >> int_)[bind(callCrane, qi::_1, qi::_2, qi::_3)];
        qi::parse(line.begin(), line.end(), rule);
    }

    return ranges::accumulate(
        stacks
            | ranges::views::transform([&](const auto& stack)
            {
                return stack.back();
            }),
        std::string{});
}

}

template <>
Result exercise<2022, 5, 1>(std::istream& stream)
{
    return exercise(stream, [&](Stacks& stacks, int cnt, int from, int to)
    {
        for (auto idx : ranges::views::indices(cnt))
        {
            stacks[to].splice(stacks[to].end(), stacks[from], std::next(stacks[from].end(), -1));
        }
    });
}


template <>
Result exercise<2022, 5, 2>(std::istream& stream)
{
    return exercise(stream, [&](Stacks& stacks, int cnt, int from, int to)
    {
        stacks[to].splice(stacks[to].end(), stacks[from], std::next(stacks[from].end(), -cnt), stacks[from].end());
    });
}

}
