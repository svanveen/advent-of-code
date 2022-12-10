#include <optional>
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

struct File
{
    std::string name;
    std::size_t size;
};

struct Directory
{
    std::size_t size() const
    {
        if (!cachedSize)
        {
            cachedSize = ranges::accumulate(files, 0, ranges::plus{}, &File::size)
                + ranges::accumulate(directories, 0, ranges::plus{}, [](const auto& entry)
                {
                    return entry.second.size();
                });
        }
        return *cachedSize;
    }

    template <typename CALLBACK>
    void visitDirectories(const CALLBACK& callback) const
    {
        callback(*this);
        for (const auto& [name, dir] : directories)
        {
            dir.visitDirectories(callback);
        }
    }

    std::string name;
    Directory* parent = nullptr;
    std::vector<File> files;
    std::map<std::string, Directory> directories;
    mutable std::optional<std::size_t> cachedSize;
};

Directory parseTree(std::istream& stream)
{
    auto root = Directory{"/"};
    auto* cwd = &root;

    for (const auto& line : ranges::getlines(stream))
    {
        using namespace boost::spirit;

        const auto cdRootAction = [&](const auto& target)
        {
            cwd = &root;

        };
        const auto cdUpAction = [&](const auto& target)
        {
            cwd = cwd->parent;
        };

        const auto cdAction = [&](const auto& target)
        {
            cwd = &(cwd->directories.at(target));
        };

        const auto fileAction = [&](std::string name, int size)
        {
            cwd->files.emplace_back(std::move(name), size);
        };

        const auto directoryAction = [&](const auto& name)
        {
            cwd->directories.try_emplace(name, name, cwd);
        };

        auto nameRule = qi::as_string[+qi::char_];
        auto commandRule = qi::lit("$ ") >> (qi::lit("ls") | (qi::lit("cd") >> qi::space >> (qi::char_('/')[cdRootAction] | qi::lit("..")[cdUpAction] | nameRule[cdAction])));

        auto lsOutputRule = (qi::int_ >> qi::omit[qi::space] >> nameRule)[boost::phoenix::bind(fileAction, qi::_2, qi::_1)] | qi::lit("dir") >> qi::space >> nameRule[directoryAction];

        qi::parse(line.begin(), line.end(), commandRule | lsOutputRule);
    }
    return root;
}

}

template <>
Result exercise<2022, 7, 1>(std::istream& stream)
{
    const auto root = parseTree(stream);

    auto totalSize = 0;
    root.visitDirectories([&](const auto& dir)
    {
        const auto size = dir.size();
        if (size <= 100'000)
        {
            totalSize += size;
        }
    });

    return totalSize;
}

template <>
Result exercise<2022, 7, 2>(std::istream& stream)
{
    const auto root = parseTree(stream);

    constexpr auto diskSpace = 70'000'000;
    constexpr auto necessaryUnusedSpace = 30'000'000;
    constexpr auto usableSpace = diskSpace - necessaryUnusedSpace;
    const auto totalSize = root.size();

    auto smallestDirSizeToDelete = totalSize;
    root.visitDirectories([&](const auto& dir)
    {
        const auto size = dir.size();
        if (totalSize - size <= usableSpace && size < smallestDirSizeToDelete)
        {
            smallestDirSizeToDelete = size;
        }
    });

    return smallestDirSizeToDelete;
}

}
