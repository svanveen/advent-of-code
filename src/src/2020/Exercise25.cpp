#include <list>
#include <string>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

template <std::size_t MOD>
auto computeEncryptionKey(std::size_t publicKey, std::size_t loopSize)
{
    auto result = std::size_t{1};
    for (std::size_t i = 0; i < loopSize; ++i)
    {
        result = (result * publicKey) % MOD;
    }
    return result;
}

template <std::size_t SUBJECT_NUMBER, std::size_t MOD>
auto computeLoopSize(std::size_t publicKey)
{
    auto tmp = std::size_t{1};
    for (std::size_t loopSize = 1; ; ++loopSize)
    {
        tmp = (tmp * SUBJECT_NUMBER) % MOD;
        if (tmp == publicKey)
        {
            return loopSize;
        }
    }
}

}

template <>
Result exercise<2020, 25, 1>(std::istream& stream)
{
    const auto publicKeys = ranges::getlines(stream)
        | ranges::views::transform([](auto&& number) { return std::stoull(number); })
        | ranges::to_vector;

    const auto loopSizes = publicKeys
        | ranges::views::transform([](auto&& publicKey) { return computeLoopSize<7, 20201227>(publicKey); })
        | ranges::to_vector;

    return computeEncryptionKey<20201227>(publicKeys.front(), loopSizes.back());
}

template <>
Result exercise<2020, 25, 2>(std::istream& stream)
{
    return 0;
}

}
