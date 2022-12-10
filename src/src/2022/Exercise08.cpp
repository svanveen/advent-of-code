#include <range/v3/algorithm/max_element.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Tree
{
    int height;
    bool visible = false;
    int scenicScore = 1;
};

using TreeGrid = std::vector<std::vector<Tree>>;

TreeGrid parseTreeGrid(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform([](const auto& row)
            {
                return row
                    | ranges::views::transform([](const auto heightChar)
                        {
                            return Tree{heightChar - '0'};
                        })
                    | ranges::to_vector;
            })
        | ranges::to_vector;
}

struct ViewDistancePerHeight
{
    int compute(int height)
    {
        auto distance = data[height];
        // all smaller or equal only see current
        for (auto idx : ranges::views::indices(height + 1))
        {
            data[idx] = 1;
        }
        // all higher see the same as before plus the current one
        for (auto idx : ranges::views::indices(height + 1, 10))
        {
            ++data[idx];
        }
        return distance;
    }

    std::array<int, 10> data = {};
};

}

template <>
Result exercise<2022, 8, 1>(std::istream& stream)
{
    auto treeGrid = parseTreeGrid(stream);

    const auto cols = treeGrid.front().size();

    auto visibleCount = 0;

    const auto iterateEntries = [&](auto& transformation)
    {
        auto heightCols = std::vector<int>(cols, -1);
        for (auto& row : treeGrid | transformation)
        {
            auto heightRow = -1;
            for (auto idx : ranges::views::indices(cols) | transformation)
            {
                auto& el = row[idx];
                if (!el.visible && (heightRow < el.height || heightCols[idx] < el.height))
                {
                    el.visible = true;
                    ++visibleCount;
                }
                heightRow = std::max(heightRow, el.height);
                heightCols[idx] = std::max(heightCols[idx], el.height);
            }
        }
    };

    iterateEntries(ranges::views::all);
    iterateEntries(ranges::views::reverse);

    return visibleCount;
}

template <>
Result exercise<2022, 8, 2>(std::istream& stream)
{
    auto treeGrid = parseTreeGrid(stream);

    const auto cols = treeGrid.front().size();

    const auto iterateEntries = [&](auto& transformation)
    {
        auto viewDistancePerHeightCols = std::vector<ViewDistancePerHeight>(cols);
        for (auto& row : treeGrid | transformation)
        {
            auto viewDistancePerHeightRow = ViewDistancePerHeight{};
            for (auto idx : ranges::views::indices(cols) | transformation)
            {
                auto& el = row[idx];
                el.scenicScore *= viewDistancePerHeightRow.compute(el.height);
                el.scenicScore *= viewDistancePerHeightCols[idx].compute(el.height);
            }
        }
    };

    iterateEntries(ranges::views::all);
    iterateEntries(ranges::views::reverse);

    const auto maxScenicScoreInRow = [](const auto& row)
    {
        return ranges::max(row | ranges::views::transform(&Tree::scenicScore));
    };

    return ranges::max(treeGrid | ranges::views::transform(maxScenicScoreInRow));
}

}
