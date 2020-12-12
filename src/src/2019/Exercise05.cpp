#include <string>
#include <aoc/Exercise.h>
#include <aoc/2019/IntCodeProgram.h>

namespace aoc
{

template <>
Result exercise<2019, 5, 1>(std::istream& stream)
{
    const IntCodeProgram prog{stream};
    return prog(1);
}

template <>
Result exercise<2019, 5, 2>(std::istream& stream)
{
    const IntCodeProgram prog{stream};
    return prog(5);
}

}
