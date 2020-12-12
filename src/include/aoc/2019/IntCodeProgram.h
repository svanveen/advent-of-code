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
        ADD           = 1,
        MULTIPLY      = 2,
        READ          = 3,
        WRITE         = 4,
        JUMP_IF_TRUE  = 5,
        JUMP_IF_FALSE = 6,
        LESS_THAN     = 7,
        EQUALS        = 8,
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
        auto value = [&](std::size_t idx, Mode mode)
        {
            switch (mode)
            {
                case Mode::IMMEDIATE: return program[idx];
                case Mode::PARAMETER: return program[program[idx]];
            }
        };

        int output = 0;
        for (std::size_t idx = 0; idx < program.size() && program[idx] != 99;)
       {
           const auto[op, m1, m2, m3] = splitOpCode(program[idx]);
           switch (op)
           {
               case Operation::READ:
                   program[program[idx + 1]] = input;
                   idx += 2;
                   break;
               case Operation::WRITE:
                   output = value(idx + 1, m1);
                   idx += 2;
                   break;
               case Operation::ADD:
               case Operation::MULTIPLY:
               case Operation::LESS_THAN:
               case Operation::EQUALS:
               {
                   const auto a = value(idx + 1, m1);
                   const auto b = value(idx + 2, m2);
                   program[program[idx + 3]] = exec(op, a, b);
                   idx += 4;
                   break;
               }
               case Operation::JUMP_IF_TRUE:
               case Operation::JUMP_IF_FALSE:
               {
                   if ((value(idx + 1, m1) != 0) ^ (op == Operation::JUMP_IF_FALSE))
                   {
                       idx = value(idx + 2, m2);
                   }
                   else
                   {
                       idx += 3;
                   }
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
            case Operation::ADD:       return a + b;
            case Operation::MULTIPLY:  return a * b;
            case Operation::LESS_THAN: return a < b;
            case Operation::EQUALS:    return a == b;
            default: throw std::logic_error{"invalid operation"};
        }
    }

private:
    std::vector<int> _program;
};

}

#endif //ADVENTOFCODE_INTCODEPROGRAM_H
