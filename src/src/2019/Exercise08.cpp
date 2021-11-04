#include <sstream>
#include <vector>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{
constexpr auto cols = 25;
constexpr auto rows = 6;

std::vector<int> getDigits(std::istream& stream)
{
    auto str = std::string{};
    std::getline(stream, str);

    return str
        | ranges::views::transform([](auto&& c) -> int { return c - '0'; })
        | ranges::to_vector;
}

}

template <>
Result exercise<2019, 8, 1>(std::istream& stream)
{
    const auto digits = getDigits(stream);
    const auto layer = ranges::min
    (
        digits | ranges::views::chunk(rows * cols),
        ranges::less{},
        [](auto&& rng) { return ranges::count(rng, 0); }
    );

    return ranges::count(layer, 1) * ranges::count(layer, 2);
}

template <>
Result exercise<2019, 8, 2>(std::istream& stream)
{
    const auto digits = getDigits(stream);

    auto v = ranges::views::ints(0, rows * cols)
        | ranges::views::transform([&](auto idx)
            {
                return digits
                    | ranges::views::drop_exactly(idx)
                    | ranges::views::stride(rows * cols)
                    | ranges::views::drop_while(ranges::bind_back(ranges::equal_to{}, 2));
            })
        | ranges::views::chunk(cols);

    auto os = std::ostringstream{};
    ranges::for_each(v, [&](auto&& row)
    {
        os << '\n';
        ranges::for_each(row, [&](auto&& entry)
        {
            os << (ranges::front(entry) == 0 ? ' ' : '#');
        });
    });

    return os.str();
}

}
