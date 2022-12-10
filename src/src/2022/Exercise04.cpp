#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

using Id = int;

struct IdRange
{
    bool contains(Id id) const
    {
        return (from <= id && id <= to);
    }

    bool contains(const IdRange& other) const
    {
        return contains(other.from) && contains(other.to);
    }

    bool overlaps(const IdRange& other) const
    {
        return contains(other.from) || contains(other.to) || other.contains(from) || other.contains(to);
    }

    Id from;
    Id to;
};

using IdRangePair = std::pair<IdRange, IdRange>;

template <typename PREDICATE>
Result exercise(std::istream& stream, PREDICATE&& predicate)
{
    return ranges::distance
    (
        ranges::getlines(stream)
            | ranges::views::filter(std::forward<PREDICATE>(predicate), [](const auto& str)
                {
                    auto regex = std::regex{R"((\d+)-(\d+),(\d+)-(\d+))"};
                    auto match = std::smatch{};
                    std::regex_match(str, match, regex);

                    return IdRangePair
                    {
                        IdRange{std::stoi(match[1]), std::stoi(match[2])},
                        IdRange{std::stoi(match[3]), std::stoi(match[4])}
                    };
                })
    );
}

}

template <>
Result exercise<2022, 4, 1>(std::istream& stream)
{
    return exercise(stream, [](const auto& pair)
    {
        const auto& [first, second] = pair;
        return first.contains(second) || second.contains(first);
    });
}

template <>
Result exercise<2022, 4, 2>(std::istream& stream)
{
    return exercise(stream, [](const auto& pair)
    {
        const auto& [first, second] = pair;
        return first.overlaps(second);
    });
}

}
