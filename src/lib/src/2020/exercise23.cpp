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
    explicit Game(std::istream& stream)
        : cups([&]()
            {
                std::string line;
                std::getline(stream, line);
                auto cupsRng = line
                    | ranges::views::tokenize(std::regex{R"(\d)"})
                    | ranges::views::transform([](auto&& number) { return std::stoi(number); });
                return std::list<int>(cupsRng.begin(), cupsRng.end());
            }())
        , min(ranges::min(cups))
        , max(ranges::max(cups))
    {}

    int operator()(int rounds)
    {
        for (int move = 0; move < rounds; ++move)
        {
            auto current = cups.begin();
            const auto value = *current;
            auto destination = findDestinationCup(std::next(current, 4), cups.end(), value);

            cups.splice(std::next(destination), cups, std::next(current), std::next(current, 4)); // move next 3 behind destination
            cups.splice(cups.end(), cups, current); // move first element to the end
        }
        if (1 != cups.front())
        {
            cups.splice(cups.begin(), cups, ranges::find(cups, 1), cups.end()); // circle 1 up front
        }
        std::stringstream stream;
        std::copy(std::next(cups.begin()), cups.end(), std::ostream_iterator<int>(stream));
        return std::stoi(stream.str());
    }

private:
    template <typename It>
    It findDestinationCup(It start, It end, int value)
    {
        while (true)
        {
            value = (value == min) ? max : value - 1;
            if (auto it = std::find(start, end, value); it != end)
            {
                return it;
            }
        }
    }

private:
    std::list<int> cups;
    int min;
    int max;
};



}

template <>
std::size_t exercise<2020, 23, 1>(std::istream& stream)
{
    Game game{stream};

    return game(100);
}

template <>
std::size_t exercise<2020, 23, 2>(std::istream& stream)
{
    return 0;
}

}
