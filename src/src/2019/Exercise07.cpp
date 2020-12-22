#include <aoc/Exercise.h>
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

struct AdvancedAmplifierControllerSoftware
    : public AmplifierControllerSoftware
{
public:
    using AmplifierControllerSoftware::AmplifierControllerSoftware;
    int operator()(int input) override
    {
        input = AmplifierControllerSoftware::operator()(input);
        for (int idx = 0; ; idx = (idx + 1) % 5)
        {
            const auto [output, halted] = amplifiers[idx](input);
            input = output;
            if (idx == 4 && halted)
            {
                break;
            }
        }
        return input;
    }
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
Result exercise<2019, 7, 1>(std::istream& stream)
{
    const IntCodeProgram program{stream};
    auto phaseSettingsOptions = getPhaseSettingsOptions({0, 1, 2, 3, 4});

    return ranges::max(
        phaseSettingsOptions
            | ranges::views::transform([&](auto&& phaseSettings) { return AmplifierControllerSoftware{program, phaseSettings}(0); })
    );
}

template <>
Result exercise<2019, 7, 2>(std::istream& stream)
{
    const IntCodeProgram program{stream};
    auto phaseSettingsOptions = getPhaseSettingsOptions({5, 6, 7, 8, 9});

    return ranges::max(
        phaseSettingsOptions
            | ranges::views::transform([&](auto&& phaseSettings) { return AdvancedAmplifierControllerSoftware{program, phaseSettings}(0); })
    );
}

}
