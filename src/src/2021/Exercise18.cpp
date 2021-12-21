#include <cassert>
#include <vector>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

class SnailfishNumber
{
private:
    struct Entry
    {
        int value;
        int depth;
    };

public:
    static SnailfishNumber parse(const std::string& str)
    {
        auto result = SnailfishNumber{};

        auto depth = int{};
        for (const auto c : str)
        {
            switch (c)
            {
                case '[':
                    ++depth;
                    break;
                case ']':
                    --depth;
                    break;
                case ',':
                    break;
                default:
                    result.entries.emplace_back(Entry{c - '0', depth});
                    break;
            }
        }
        return result;
    }

    SnailfishNumber operator+(const SnailfishNumber& other) const
    {
        auto result = SnailfishNumber{};
        result.entries.reserve(entries.size() + other.entries.size());
        for (const auto& entry : entries)
        {
            result.entries.push_back(entry);
        }
        for (const auto& entry : other.entries)
        {
            result.entries.push_back(entry);
        }

        if (!entries.empty() && ! other.entries.empty())
        {
            for (auto& entry : result.entries)
            {
                ++entry.depth;
            }
        }

        result.reduce();

        return result;
    }

    void reduce()
    {
        while (explode() || split());
    }

    int magnitude() const
    {
        auto e = entries;

        while (e.size() > 1)
        {
            for (auto it = e.begin(); it != e.end(); ++it)
            {
                const auto next = std::next(it);
                if (it->depth == next->depth)
                {
                    it->value = 3 * it->value + 2 * next->value;
                    --it->depth;
                    e.erase(next);
                    break;
                }
            }
        }
        return e.front().value;
    }

private:
    bool explode()
    {
        const auto it = ranges::find_if(entries, [](const auto& entry) { return entry.depth == 5; });
        if (it != ranges::end(entries))
        {
            assert(ranges::next(it) != ranges::end(entries) && ranges::next(it)->depth == 5);
            if (it != ranges::begin(entries))
            {
                ranges::next(it, -1)->value += it->value;
            }
            if (ranges::next(it, 2) != ranges::end(entries))
            {
                ranges::next(it, 2)->value += ranges::next(it)->value;
            }
            it->value = 0;
            --it->depth;
            entries.erase(ranges::next(it));
            return true;
        }
        return false;
    }

    bool split()
    {
        const auto it = ranges::find_if(entries, [](const auto& entry) { return entry.value > 9; });
        if (it != ranges::end(entries))
        {
            const auto left = static_cast<int>(std::floor(it->value / 2.));
            const auto right = static_cast<int>(std::ceil(it->value / 2.));
            it->value = right;
            ++it->depth;
            entries.insert(it, Entry{left, it->depth});
            return true;
        }
        return false;
    }

private:
    std::vector<Entry> entries;
};

}

template <>
Result exercise<2021, 18, 1>(std::istream& stream)
{
    return ranges::accumulate
    (
        ranges::getlines(stream)
            | ranges::views::transform(SnailfishNumber::parse),
        SnailfishNumber{}
    ).magnitude();
}

template <>
Result exercise<2021, 18, 2>(std::istream& stream)
{
    const auto numbers = ranges::getlines(stream)
        | ranges::views::transform(SnailfishNumber::parse)
        | ranges::to_vector;

    return ranges::max
    (
        ranges::views::cartesian_product(numbers, numbers)
            | ranges::views::transform([](const auto& tup)
            {
                const auto& [lhs, rhs] = tup;
                return (lhs + rhs).magnitude();
            })
    );
}

}
