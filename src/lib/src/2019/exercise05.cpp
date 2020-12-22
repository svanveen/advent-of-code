#include <string>
#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

template <>
std::size_t exercise<2019, 5, 1>(std::istream& stream)
{
    IntCodeProgram prog{stream};
    return prog(1).first;
}

template <>
std::size_t exercise<2019, 5, 2>(std::istream& stream)
{
    IntCodeProgram prog{stream};
    return prog(5).first;
}

}
