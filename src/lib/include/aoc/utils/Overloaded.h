#ifndef ADVENTOFCODE_OVERLOADED_H
#define ADVENTOFCODE_OVERLOADED_H

namespace aoc::utils
{

template<typename ...Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template<typename ...Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}

#endif //ADVENTOFCODE_OVERLOADED_H
