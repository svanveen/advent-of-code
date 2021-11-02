#include <string>
#include <variant>
#include <aoc/Exercise.h>
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
    MaskUpdate(const std::string& pullUp, const std::string& pullDown, const std::string& floating)
        : pullUpMask(pullUp)
        , pullDownMask(pullDown)
        , floatingMask(floating)
    {}

    BitSet pullUpMask;
    BitSet pullDownMask;
    BitSet floatingMask;
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
            auto floating = ranges::make_iterator_range(match[1].first, match[1].second)
                | ranges::views::replace('1', '0')
                | ranges::views::replace('X', '1');
            return MaskUpdate{
                std::string{pullUp.begin(), pullUp.end()},
                std::string{pullDown.begin(), pullDown.end()},
                std::string{floating.begin(), floating.end()}
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

class AbstractDecoderChip
{
public:
    virtual ~AbstractDecoderChip() = default;

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

protected:
    virtual void exec(const ValueWrite& valueWrite) = 0;

private:
    void exec(const MaskUpdate& maskUpdate)
    {
        mask = maskUpdate;
    }

protected:
    std::map<uint64_t, uint64_t> memoryMap;
    MaskUpdate mask;
};

class DecoderChip : public AbstractDecoderChip
{
    void exec(const ValueWrite& valueWrite) override
    {
        auto bits = BitSet{valueWrite.value};
        bits |= mask.pullUpMask;
        bits &= mask.pullDownMask;
        memoryMap[valueWrite.address] = bits.to_ullong();
    }

};

class DecoderChip2 : public AbstractDecoderChip
{
    void writeValue(BitSet address, uint64_t value, std::size_t idx = 35)
    {
        if (idx == 0)
        {
            memoryMap[address.to_ullong()] = value;
            if (mask.floatingMask.test(idx))
            {
                memoryMap[address.flip(idx).to_ullong()] = value;
            }
        }
        else
        {
            writeValue(address, value, idx - 1);
            if (mask.floatingMask.test(idx))
            {
                writeValue(address.flip(idx), value, idx - 1);
            }
        }
    }

    void exec(const ValueWrite& valueWrite) override
    {
        auto address = BitSet{valueWrite.address} | mask.pullUpMask;

        writeValue(address, valueWrite.value);
    }
};

template <typename DECODER_CHIP>
std::size_t exercise(std::istream& stream)
{
    auto instructions = ranges::getlines(stream)
        | ranges::views::transform(parse);

    DECODER_CHIP decoderChip;
    for (auto&& instruction : instructions)
    {
        decoderChip(instruction);
    }

    return ranges::accumulate(decoderChip.getMemoryMap() | ranges::views::values, std::size_t{0});
}

}

template <>
Result exercise<2020, 14, 1>(std::istream& stream)
{
    return exercise<DecoderChip>(stream);
}

template <>
Result exercise<2020, 14, 2>(std::istream& stream)
{
    return exercise<DecoderChip2>(stream);
}

}
