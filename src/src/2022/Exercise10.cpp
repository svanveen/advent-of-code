#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

template <typename CALLBACK>
void exercise(std::istream& stream, CALLBACK&& callback)
{
    int cycle = 0;
    int x = 1;

    const auto nextCycle = [&]()
    {
        ++cycle;
        callback(cycle, x);
    };

    for (const auto& line : ranges::getlines(stream))
    {
        if (line == "noop"sv)
        {
            nextCycle();
        }
        else
        {
            const auto v = std::atoi(&line[line.find(' ') + 1]);
            nextCycle();
            nextCycle();
            x += v;
        }
    }
}

}

using namespace std::string_view_literals;

template <>
Result exercise<2022, 10, 1>(std::istream& stream)
{
    auto result = 0;
    exercise(stream, [&](int cycle, int x)
    {
        if (cycle >= 20 && ((cycle - 20) % 40 == 0))
        {
            result += cycle * x;
        }
    });
    return result;
}

template <>
Result exercise<2022, 10, 2>(std::istream& stream)
{
    auto os = std::ostringstream{};
    exercise(stream, [&](int cycle, int x)
    {
        os << ((std::abs((cycle - 1) % 40 - x) <= 1) ? '#' : '.');
        if (cycle % 40 == 0)
        {
            os << '\n';
        }
    });
    return os.str();
}

}
