#include <string>
#include <aoc/exercises.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

template <>
std::size_t exercise<2019, 5, 1>(std::istream& stream)
{
    const IntCodeProgram prog{stream};
    return prog(1);
}

template <>
std::size_t exercise<2019, 5, 2>(std::istream& stream)
{
    return 0;
}

}
