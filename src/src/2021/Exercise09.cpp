#include <range/v3/action.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{
auto getDepths(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(ranges::views::all | ranges::views::transform(ranges::bind_back(ranges::minus{}, '0')))
        | ranges::views::transform(ranges::to_vector)
        | ranges::to_vector;
}


std::size_t basinSize(std::vector<std::vector<int>>& depths, std::size_t r, std::size_t c)
{
    const auto rows = depths.size();
    const auto cols = depths[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || depths[r][c] == 9)
    {
        return 0;
    }
    depths[r][c] = 9; // invalidate position
    return 1
        + basinSize(depths, r - 1, c)
        + basinSize(depths, r + 1, c)
        + basinSize(depths, r, c - 1)
        + basinSize(depths, r, c + 1);
}

}

template <>
Result exercise<2021, 9, 1>(std::istream& stream)
{
    const auto depths = getDepths(stream);
    const auto rows = depths.size();
    const auto cols = depths[0].size();

    auto result = int{};
    for (auto r = 0; r < rows; ++r)
    {
        for (auto c = 0; c < cols; ++c)
        {
            const auto& current = depths[r][c];
            if (r > 0 && depths[r - 1][c] <= current)
            {
                continue;
            }
            if (r < rows - 1 && depths[r + 1][c] <= current)
            {
                continue;
            }
            if (c > 0 && depths[r][c - 1] <= current)
            {
                continue;
            }
            if (c < cols - 1 && depths[r][c + 1] <= current)
            {
                continue;
            }
            result += (current + 1);
        }
    }
    return result;
}

template <>
Result exercise<2021, 9, 2>(std::istream& stream)
{
    auto depths = getDepths(stream);
    const auto rows = depths.size();
    const auto cols = depths[0].size();

    auto sizes = ranges::views::cartesian_product(ranges::views::ints(std::size_t{0}, rows), ranges::views::ints(std::size_t{0}, cols))
        | ranges::views::transform([&](auto&& tup)
        {
            const auto[r, c] = tup;
            return basinSize(depths, r, c);
        })
        | ranges::to_vector
        | ranges::actions::sort(ranges::greater{})
        | ranges::actions::take(3);

    return ranges::accumulate(sizes, std::size_t{1}, ranges::multiplies{});
}

}
