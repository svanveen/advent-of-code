#ifndef ADVENTOFCODE_INTCODEPROGRAM_H
#define ADVENTOFCODE_INTCODEPROGRAM_H

#include <fstream>
#include <string>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

namespace aoc
{

class IntCodeProgram
{
public:
    explicit IntCodeProgram(std::istream& stream)
        : _program(parseProgram(stream))
    {}

    std::size_t operator()(std::size_t noun, std::size_t verb) const
    {
        auto program = _program;
        program[1] = noun;
        program[2] = verb;
        auto instructions = program
            | ranges::views::chunk(4)
            | ranges::views::take_while(ranges::bind_back(ranges::not_equal_to{}, 99), ranges::front);

        ranges::for_each(instructions, [&](auto&& instruction)
        {
            const auto a = program[ranges::at(instruction, 1)];
            const auto b = program[ranges::at(instruction, 2)];
            auto& c = program[ranges::at(instruction, 3)];
            c = performOperation(ranges::at(instruction, 0), a, b);
        });

        return program[0];
    }

private:
    static std::vector<int> parseProgram(std::istream& stream)
    {
        return ranges::getlines(stream, ',')
            | ranges::views::transform([](auto&& s) { return std::stoi(s); })
            | ranges::to_vector;
    }

    static std::size_t performOperation(int op, std::size_t a, std::size_t b)
    {
        switch(op)
        {
            case 1: return a + b;
            case 2: return a * b;
            default: throw std::logic_error{"invalid operation"};
        }
    }

private:
    std::vector<int> _program;
};

}

#endif //ADVENTOFCODE_INTCODEPROGRAM_H
