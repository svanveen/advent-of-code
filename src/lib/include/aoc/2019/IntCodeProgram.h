#ifndef ADVENTOFCODE_INTCODEPROGRAM_H
#define ADVENTOFCODE_INTCODEPROGRAM_H

#include <cassert>
#include <fstream>
#include <string>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

namespace aoc
{

class IntCodeProgram
{
private:
    enum class Operation
    {
        ADD      = 01,
        MULTIPLY = 02,
        READ     = 03,
        WRITE    = 04,
    };

    enum class Mode
    {
        PARAMETER = 0,
        IMMEDIATE = 1,
    };

    static std::tuple<Operation, Mode, Mode, Mode> splitOpCode(int value)
    {
        return std::tuple{
            static_cast<Operation>(value % 100),
            static_cast<Mode>((value % 1000) / 100),
            static_cast<Mode>((value % 10000) / 1000),
            static_cast<Mode>((value % 100000) / 10000),
        };
    }



public:
    explicit IntCodeProgram(std::istream& stream)
        : _program(parseProgram(stream))
    {}

    int operator()(int noun, int verb) const
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
            c = exec(static_cast<Operation>(ranges::at(instruction, 0)), a, b);
        });

        return program[0];
    }

    int operator()(int input) const
    {
        auto program = _program;
        auto value = [&](int parameter, Mode mode)
        {
            switch (mode)
            {
                case Mode::IMMEDIATE: return parameter;
                case Mode::PARAMETER: return program[parameter];
            }
        };

        int output = 0;
        for (std::size_t idx = 0; idx < program.size() && program[idx] != 99;)
       {
           assert(output == 0);
           const auto[op, m1, m2, m3] = splitOpCode(program[idx]);
           switch (op)
           {
               case Operation::READ:
                   program[program[idx + 1]] = input;
                   idx += 2;
                   break;
               case Operation::WRITE:
                   output = value(program[idx + 1], m1);
                   idx += 2;
                   break;
               case Operation::ADD:
               case Operation::MULTIPLY:
               {
                   const auto a = value(program[idx + 1], m1);
                   const auto b = value(program[idx + 2], m2);
                   program[program[idx + 3]] = exec(op, a, b);
                   idx += 4;
                   break;
               }
           }
       }
       return output;
    }

private:
    static std::vector<int> parseProgram(std::istream& stream)
    {
        return ranges::getlines(stream, ',')
            | ranges::views::transform([](auto&& s) { return std::stoi(s); })
            | ranges::to_vector;
    }


    static int exec(Operation op, int a, int b)
    {
        switch(op)
        {
            case Operation::ADD:      return a + b;
            case Operation::MULTIPLY: return a * b;
            default: throw std::logic_error{"invalid operation"};
        }
    }

private:
    std::vector<int> _program;
};

}

#endif //ADVENTOFCODE_INTCODEPROGRAM_H
