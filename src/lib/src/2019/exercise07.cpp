#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

namespace
{

int computeBestResult(const IntCodeProgram& program, std::vector<int> phaseSettings, int input)
{
    auto compute = [&](int phaseSetting)
    {
        const auto output = program({phaseSetting, input});
        if (phaseSettings.size() == 1)
        {
            return output;
        }
        else
        {
            return computeBestResult(program, phaseSettings | ranges::views::remove(phaseSetting) | ranges::to_vector, output);
        }
    };

    return ranges::max(phaseSettings | ranges::views::transform(compute));
}

}

template <>
std::size_t exercise<2019, 7, 1>(std::istream& stream)
{
    const IntCodeProgram program{stream};
    return computeBestResult(program, ranges::views::closed_iota(0, 4) | ranges::to_vector, 0);
}

template <>
std::size_t exercise<2019, 7, 2>(std::istream& stream)
{
    return 0;
}

}
