#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace {

auto getEnergyLevels(std::istream &stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(ranges::views::all | ranges::views::transform(ranges::bind_back(ranges::minus{}, '0')))
        | ranges::views::transform(ranges::to_vector)
        | ranges::to_vector;
}

std::size_t update(std::vector<std::vector<int>>& energyLevels, std::size_t r, std::size_t c)
{
    const auto rows = energyLevels.size();
    const auto cols = energyLevels[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        return 0;
    }
    if (++energyLevels[r][c] == 10)
    {
        auto flashes = std::size_t{1};
        for (const auto dr : {-1, 0, 1})
        {
            for (const auto dc : {-1, 0, 1})
            {
                if (dr != 0 || dc != 0)
                {
                    flashes += update(energyLevels, r + dr, c + dc);
                }
            }
        }
        return flashes;
    }
    return 0;
}

std::size_t update(std::vector<std::vector<int>>& energyLevels)
{
    const auto rows = energyLevels.size();
    const auto cols = energyLevels[0].size();

    auto flashes = std::size_t{};
    for (auto r = 0; r < rows; ++r)
    {
        for (auto c = 0; c < cols; ++c)
        {
            flashes += update(energyLevels, r, c);
        }
    }
    for (auto r = 0; r < rows; ++r)
    {
        for (auto c = 0; c < cols; ++c)
        {
            if (energyLevels[r][c] > 9)
            {
                energyLevels[r][c] = 0;
            }
        }
    }
    return flashes;
}

}

template <>
Result exercise<2021, 11, 1>(std::istream& stream)
{
    auto energyLevels = getEnergyLevels(stream);

    auto flashes = std::size_t{};
    for (auto step = 0; step < 100; ++step)
    {
        flashes += update(energyLevels);
    }

    return flashes;
}

template <>
Result exercise<2021, 11, 2>(std::istream& stream)
{
    auto energyLevels = getEnergyLevels(stream);
    const auto rows = energyLevels.size();
    const auto cols = energyLevels[0].size();

    for (auto step = 1;; ++step)
    {
        if (update(energyLevels) == rows * cols)
        {
            return step;
        }
    }
}

}
