#include <string>
#include <variant>
#include <aoc/exercises.h>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <range/v3/iterator_range.hpp>

namespace aoc
{

namespace
{

using BitSet = std::bitset<36>;

struct MaskUpdate
{
    MaskUpdate() = default;
    MaskUpdate(const std::string& pullUp, const std::string& pullDown)
        : pullUpMask(pullUp)
        , pullDownMask(pullDown)
    {}

    BitSet pullUpMask;
    BitSet pullDownMask;
};

struct ValueWrite
{
    uint64_t address;
    uint64_t value;
};

using Instruction = std::variant<MaskUpdate, ValueWrite>;

Instruction parse(const std::string& str)
{
    {
        static const std::regex regex{R"(mask = ([X01]{36}))"};
        std::smatch match;
        if (std::regex_match(str, match, regex))
        {
            auto pullUp = ranges::make_iterator_range(match[1].first, match[1].second)
                | ranges::views::replace('X', '0');
            auto pullDown = ranges::make_iterator_range(match[1].first, match[1].second)
                | ranges::views::replace('X', '1');
            return MaskUpdate{
                std::string{pullUp.begin(), pullUp.end()},
                std::string{pullDown.begin(), pullDown.end()}
            };
        }
    }
    {
        static const std::regex regex{R"(mem\[(\d+)\] = (\d+))"};
        std::smatch match;
        if (std::regex_match(str, match, regex))
        {
            return ValueWrite{std::stoull(match[1]), std::stoull(match[2])};
        }
    }
    throw std::runtime_error{"could not parse instruction"};
}

class Program
{
public:
    void operator()(const Instruction& instruction)
    {
        std::visit([&](auto&& instr)
        {
            exec(instr);
        }, instruction);
    }

    const std::map<uint64_t, uint64_t >& getMemoryMap() const
    {
        return memoryMap;
    }

private:
    void exec(const ValueWrite& valueWrite)
    {
        auto bits = BitSet{valueWrite.value};
        bits |= mask.pullUpMask;
        bits &= mask.pullDownMask;
        memoryMap[valueWrite.address] = bits.to_ullong();
    }

    void exec(const MaskUpdate& maskUpdate)
    {
        mask = maskUpdate;
    }

private:
    std::map<uint64_t, uint64_t> memoryMap;
    MaskUpdate mask;
};

}

template <>
std::size_t exercise<2020, 14, 1>(std::istream& stream)
{
    auto instructions = ranges::getlines(stream)
        | ranges::views::transform(parse);

    Program program;
    for (auto&& instruction : instructions)
    {
        program(instruction);
    }

    return ranges::accumulate(program.getMemoryMap() | ranges::views::values, std::size_t{0});
}

template <>
std::size_t exercise<2020, 14, 2>(std::istream& stream)
{
    return 0;
}

}
