#include <cassert>
#include <iomanip>
#include <limits>
#include <type_traits>
#include <variant>
#include <vector>
#include <unordered_map>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

constexpr auto sum     = ranges::bind_back(ranges::accumulate, std::size_t{0}, ranges::plus{});
constexpr auto product = ranges::bind_back(ranges::accumulate, std::size_t{1}, ranges::multiplies{});
constexpr auto minimum = ranges::bind_back(ranges::accumulate, std::numeric_limits<std::size_t>::max(), ranges::min_fn{});
constexpr auto maximum = ranges::bind_back(ranges::accumulate, std::size_t{0}, ranges::max_fn{});

constexpr auto greaterThan = [](const std::vector<std::size_t>& values) -> std::size_t
{
    return values.front() > values.back();
};

constexpr auto lessThan = [](const std::vector<std::size_t>& values) -> std::size_t
{
    return values.front() < values.back();
};

constexpr auto equal = [](const std::vector<std::size_t>& values) -> std::size_t
{
    return values.front() == values.back();
};

using Operation = std::variant
<
    decltype(sum),
    decltype(product),
    decltype(minimum),
    decltype(maximum),
    decltype(greaterThan),
    decltype(lessThan),
    decltype(equal)
>;

const auto operations = std::unordered_map<std::uint8_t, Operation>
{
    {0, sum},
    {1, product},
    {2, minimum},
    {3, maximum},
    {5, greaterThan},
    {6, lessThan},
    {7, equal}
};

struct Remainder
{
    uint8_t consume(std::size_t bitsToConsume)
    {
        assert(bitsToConsume <= bits);
        const auto result = (value >> (bits - bitsToConsume));
        value -= (result << (bits - bitsToConsume));
        bits -= bitsToConsume;
        return result;
    }

    uint8_t consume()
    {
        const auto result = value;
        value = 0;
        bits = 0;
        return result;
    }

    std::uint8_t value = {};
    std::size_t bits = {};
};

class BitConsumer
{
public:
    explicit BitConsumer(const std::string& str)
        : iterator(str.begin())
        , end(str.end())
    {}

    std::size_t getConsumed() const
    {
        return consumed;
    }

    template <typename UINT>
    UINT consume(std::size_t bits)
    {
        static_assert(std::is_unsigned_v<UINT>);

        consumed += bits;

        if (bits < remainder.bits)
        {
            return remainder.consume(bits);
        }

        bits -= remainder.bits;
        auto result = remainder.consume();

        const auto end = std::next(iterator, bits / 4);
        for (; iterator != end; ++iterator)
        {
            result <<= 4u;
            result |= hexToBinary(*iterator);
            bits -= 4;
        }

        if (bits > 0)
        {
            remainder = Remainder{hexToBinary(*iterator++), 4};
            result <<= bits;
            result |= remainder.consume(bits);
        }
        return result;
    }

private:
    static uint8_t hexToBinary(char c)
    {
        return static_cast<uint8_t>((c >= '0' && c <= '9') ? (c - '0') : (10 + (c - 'A')));
    }

private:
    std::string::const_iterator iterator;
    std::string::const_iterator end;
    Remainder remainder;
    std::size_t consumed;
};

struct Packet
{
    Packet(std::uint8_t version, std::uint8_t typeId, std::uint64_t value)
        : header{version, typeId}
        , value(value)
    {}

    struct Header
    {
        std::uint8_t version;
        std::uint8_t typeId;
    };

    Header header;
    std::uint64_t value;
};

class Packets
{
public:
    explicit Packets(const std::string& str)
    {
        auto bitConsumer = BitConsumer{str};
        parsePacket(bitConsumer);
    }

    std::size_t getPackageVersionSum() const
    {
        return ranges::accumulate(data, std::size_t{0}, ranges::plus{}, [](const auto& packet)
        {
            return packet.header.version;
        });
    }

    std::size_t getValue()
    {
        return data.back().value;
    }

private:
    uint64_t parsePacket(BitConsumer& consumer)
    {
        const auto version = consumer.consume<uint8_t>(3);
        const auto typeId  = consumer.consume<uint8_t>(3);

        auto value = std::size_t{};
        if (typeId == 4)
        {
            for (;;)
            {
                const auto block = consumer.consume<uint8_t>(5);
                value = (value << 4u) | (block & 0b1111u);
                if ((block & 0b10000u) == 0)
                {
                    break;
                }
            }
        }
        else
        {
            auto subvalues = std::vector<std::size_t>{};
            const auto lengthTypeId = consumer.consume<uint8_t>(1);
            if (lengthTypeId == 0)
            {
                const auto totalLength = consumer.consume<uint16_t>(15);
                const auto initial = consumer.getConsumed();
                while (consumer.getConsumed() < initial + totalLength)
                {
                    subvalues.emplace_back(parsePacket(consumer));
                }
            }
            else
            {
                const auto subpacketCount = consumer.consume<uint16_t>(11);
                data.reserve(data.size() + subpacketCount);
                for (std::size_t i = 0; i < subpacketCount; ++i)
                {
                    subvalues.emplace_back(parsePacket(consumer));
                }
            }
            value = std::visit
            (
                [&](const auto& operation) { return operation(subvalues); },
                operations.at(typeId)
            );
        }
        data.emplace_back(version, typeId, value);
        return value;
    }

private:
    std::vector<Packet> data;
};

}

template <>
Result exercise<2021, 16, 1>(std::istream& stream)
{
    auto packets = Packets{(*ranges::getlines(stream).begin())};
    return packets.getPackageVersionSum();
}

template <>
Result exercise<2021, 16, 2>(std::istream& stream)
{
    auto packets = Packets{(*ranges::getlines(stream).begin())};
    return packets.getValue();
}

}
