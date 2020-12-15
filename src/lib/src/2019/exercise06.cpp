#include <memory>
#include <regex>
#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

using Object = std::string;

struct Connection
{
    Object parent;
    Object child;

    static Connection parse(const std::string& str)
    {
        static const auto regex = std::regex{R"((\w+)\)(\w+))"};
        std::smatch match;
        std::regex_match(str, match, regex);
        return Connection{match[1].str(), match[2].str()};
    }
};

struct Node
{
    explicit Node(const Object& orbit)
        : orbit(orbit)
    {}

    Object orbit;
    std::vector<std::unique_ptr<Node>> children;
};

struct Tree
{
    template <typename CONNECTIONS>
    Tree(CONNECTIONS&& connections)
    {
        std::map<Object, std::unique_ptr<Node>> nodes;
        std::map<Object, Node*> addressMap;
        for (auto&& connection : connections)
        {
            auto parent = nodes[connection.parent].get();
            if (!parent)
            {
                parent = addressMap[connection.parent];
            }
            if (!parent)
            {
                parent = (nodes[connection.parent] = std::make_unique<Node>(connection.parent)).get();
            }
            auto& child = nodes[connection.child];
            if (!child)
            {
                child = std::make_unique<Node>(connection.child);
            }
            addressMap[connection.child] = child.get();
            parent->children.emplace_back(std::move(child));
        }

        auto rootNodes = nodes
            | ranges::views::values
            | ranges::views::filter([](auto&& nodePtr) -> bool { return nodePtr.operator bool(); });
        root = std::move(ranges::front(rootNodes));
    }

    std::unique_ptr<Node> root;
};

std::size_t countOrbits(const Node& node, std::size_t distance = 0)
{
    auto childrensOrbits = node.children
       | ranges::views::indirect
       | ranges::views::transform(ranges::bind_back(countOrbits, distance + 1));
    return ranges::accumulate(childrensOrbits, std::size_t{distance});
}


}

template <>
std::size_t exercise<2019, 6, 1>(std::istream& stream)
{
    auto connections = ranges::getlines(stream)
        | ranges::views::transform(Connection::parse);

    auto tree = Tree(connections);

    return countOrbits(*tree.root);
}

template <>
std::size_t exercise<2019, 6, 2>(std::istream& stream)
{
    return 0;
}

}
