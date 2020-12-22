#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

namespace
{

class AmplifierControllerSoftware
{
public:
    explicit AmplifierControllerSoftware(const IntCodeProgram& program, const std::array<int, 5>& phaseSettings)
        : amplifiers({program, program, program, program, program})
        , phaseSettings(phaseSettings)
    {}
    virtual ~AmplifierControllerSoftware() = default;

    virtual int operator()(int input)
    {
        return eval(input);
    }

protected:
    int eval(int input)
    {
        for (int idx = 0; idx < 5; ++idx)
        {
            const auto [output, _] = amplifiers[idx]({phaseSettings[idx], input});
            input = output;
        }
        return input;
    }

protected:
    std::array<IntCodeProgram, 5> amplifiers;
    std::array<int, 5> phaseSettings;
};

auto getPhaseSettingsOptions(std::array<int, 5> phaseSettings)
{
    return ranges::views::generate_n([&]()
    {
        auto settings = phaseSettings;
        ranges::next_permutation(phaseSettings);
        return settings;
    }, 120);
}

}

template <>
std::size_t exercise<2019, 7, 1>(std::istream& stream)
{
    const IntCodeProgram program{stream};
    auto phaseSettingsOptions = getPhaseSettingsOptions({0, 1, 2, 3, 4});

    return ranges::max(
        phaseSettingsOptions
            | ranges::views::transform([&](auto&& phaseSettings) { return AmplifierControllerSoftware{program, phaseSettings}(0); })
    );
}

template <>
std::size_t exercise<2019, 7, 2>(std::istream& stream)
{
    return 0;
}

}
