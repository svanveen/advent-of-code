#include <memory>
#include <regex>
#include <string>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

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
        : object(orbit)
    {}

    Object object;
    Node* parent;
    std::vector<std::unique_ptr<Node>> children;
};

struct Tree
{
    Tree(std::istream& stream)
    {
        auto connections = ranges::getlines(stream)
            | ranges::views::transform(Connection::parse);

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
            child->parent = parent;
            addressMap[connection.child] = child.get();
            parent->children.emplace_back(std::move(child));
        }

        auto rootNodes = nodes
            | ranges::views::values
            | ranges::views::filter([](auto&& nodePtr) -> bool { return nodePtr.operator bool(); });
        root = std::move(ranges::front(rootNodes));
    }

    std::pair<const Node*, int> findNode(const Object& object, const Node& node, int depth = 0)
    {
        if (node.object == object)
        {
            return std::pair{&node, depth};
        }
        for (const auto& child : node.children)
        {
            auto childResult = findNode(object, *child, depth + 1);
            if (childResult.first)
            {
                return childResult;
            }
        }
        return std::pair{nullptr, 0};
    }

    auto findNode(const Object& object)
    {
        return findNode(object, *root);
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
Result exercise<2019, 6, 1>(std::istream& stream)
{
    auto tree = Tree{stream};

    return countOrbits(*tree.root);
}

template <>
Result exercise<2019, 6, 2>(std::istream& stream)
{
    auto tree = Tree{stream};

    auto you = tree.findNode("YOU");
    auto san = tree.findNode("SAN");

    auto parent = [](auto&& pair) { return std::pair{pair.first->parent, pair.second - 1}; };

    int connections = 0;
    for (; you.first != san.first; )
    {
        const auto depthYou = you.second;
        const auto depthSan = san.second;
        if (depthYou <= depthSan)
        {
            san = parent(san);
            ++connections;
        }
        if (depthYou >= depthSan)
        {
            you = parent(you);
            ++connections;
        }
    }

    return connections - 2; // Remove first connection on both ends
}

}
