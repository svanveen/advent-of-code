#include <list>
#include <string>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct Game
{
    explicit Game(std::istream& stream, std::optional<int> fillUpTo = {})
        : cups([&]()
            {
                std::string line;
                std::getline(stream, line);
                auto cupsRng = line
                    | ranges::views::tokenize(std::regex{R"(\d)"})
                    | ranges::views::transform([](auto&& number) { return std::stoi(number); });
                if (fillUpTo)
                {
                    auto extendedCupsRng = ranges::views::concat(
                        cupsRng,
                        ranges::views::closed_iota(ranges::max(cupsRng) + 1, *fillUpTo)
                    );
                    return std::list<int>(extendedCupsRng.begin(), extendedCupsRng.end());
                }
                return std::list<int>(cupsRng.begin(), cupsRng.end());
            }())
        , min(ranges::min(cups))
        , max(ranges::max(cups))
    {
        for (auto it = cups.begin(); it != cups.end(); ++it)
        {
            iteratorMap.emplace(*it, it); // this only works since std::list doesn't invalidate it's iterators on any change
        }
    }

    const std::list<int>& getCups()
    {
        return cups;
    }

    void play(int rounds)
    {
        for (std::size_t move = 0; move < rounds; ++move)
        {
            auto current = cups.begin();
            const auto value = *current;
            const auto destinationValue = findDestinationCupValue(std::next(current), std::next(current, 4), value);
            const auto destination = iteratorMap[destinationValue];

            cups.splice(std::next(destination), cups, std::next(current), std::next(current, 4)); // move next 3 behind destination
            cups.splice(cups.end(), cups, current); // move first element to the end
        }
        if (1 != cups.front())
        {
            cups.splice(cups.begin(), cups, ranges::find(cups, 1), cups.end()); // circle 1 up front
        }
    }

private:
    template <typename It>
    int findDestinationCupValue(It start, It end, int value)
    {
        while (true)
        {
            value = (value == min) ? max : value - 1;
            if (std::find(start, end, value) == end)
            {
                return value;
            }
        }
    }

private:
    std::list<int> cups;
    std::map<int, std::list<int>::iterator> iteratorMap;
    int min;
    int max;
};



}

template <>
Result exercise<2020, 23, 1>(std::istream& stream)
{
    Game game{stream};
    game.play(100);

    const auto& cups = game.getCups();
    std::stringstream sstream;
    std::copy(std::next(cups.begin()), cups.end(), std::ostream_iterator<int>(sstream));
    return std::stoi(sstream.str());
}

template <>
Result exercise<2020, 23, 2>(std::istream& stream)
{
    Game game{stream, 1'000'000};
    game.play(10'000'000);

    const auto& cups = game.getCups();
    return static_cast<std::size_t>(*std::next(cups.begin())) * static_cast<std::size_t>(*std::next(cups.begin(), 2));
}

}
