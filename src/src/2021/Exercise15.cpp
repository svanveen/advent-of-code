#include <optional>
#include <queue>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

struct Node
{
    Node(std::size_t row, std::size_t col, int riskLevel)
        : row(row)
        , col(col)
        , riskLevel(riskLevel)
    {}

    std::size_t row;
    std::size_t col;
    int riskLevel;
    std::optional<int> dist = {};
};

constexpr auto compareNodes = [](Node* const lhs, Node* const rhs)
{
    return lhs->dist > rhs->dist;
};

auto createNodes(std::istream& stream, std::size_t tiles = 1)
{
    auto riskLevels = ranges::getlines(stream)
        | ranges::views::transform(ranges::views::all | ranges::views::transform(ranges::bind_back(ranges::minus{}, '0')) | ranges::to_vector)
        | ranges::to_vector;

    const auto rows = riskLevels.size();
    const auto cols = riskLevels.front().size();

    auto nodes = std::vector<std::vector<Node>>{};
    nodes.resize(rows * tiles);
    for (std::size_t r = 0; r < rows * tiles; ++r)
    {
        nodes[r].reserve(cols * tiles);
        for (std::size_t c = 0; c < cols * tiles; ++c)
        {
            const auto riskLevel = (riskLevels[r % rows][c % cols] + static_cast<int>(r / rows + c / cols) - 1) % 9 + 1;
            nodes[r].emplace_back(r, c, riskLevel);
        }
    }
    return nodes;
}

// implementation of Dijkstra algorithm
std::size_t computeBestRiskLevelPath(std::vector<std::vector<Node>> nodes, std::size_t tiles = 1)
{
    const auto rows = nodes.size();
    const auto cols = nodes.front().size();

    auto queue = std::priority_queue<Node*,std::vector<Node*>, decltype(compareNodes)>{compareNodes};
    nodes[0][0].dist = 0;
    queue.emplace(&nodes[0][0]);

    while (!queue.empty())
    {
        const auto& node = *queue.top();
        if (node.row == rows - 1 && node.col == cols - 1)
        {
            return *node.dist;
        }
        queue.pop();
        for (const auto [dr, dc] : std::array<std::pair<int, int>, 4>{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}})
        {
            if ((node.row == 0 && dr < 0) || (node.col == 0 && dc < 0))
            {
                continue;
            }

            const auto nextRow = node.row + dr;
            const auto nextCol = node.col + dc;

            if ((nextRow >= rows) || (nextCol >= cols))
            {
                continue;
            }

            auto& next = nodes[nextRow][nextCol];
            const auto newNode = !next.dist;
            const auto alternative = *node.dist + next.riskLevel;
            if (!next.dist || next.dist > alternative)
            {
                next.dist = alternative;
            }
            if (newNode)
            {
                next.row = nextRow;
                next.col = nextCol;
                queue.emplace(&next);
            }
        }
    }
    throw std::logic_error{"no path found"};
}

}

template <>
Result exercise<2021, 15, 1>(std::istream& stream)
{
    auto nodes = createNodes(stream);
    return computeBestRiskLevelPath(std::move(nodes));
}

template <>
Result exercise<2021, 15, 2>(std::istream& stream)
{
    auto nodes = createNodes(stream, 5);
    return computeBestRiskLevelPath(std::move(nodes));
}

}
