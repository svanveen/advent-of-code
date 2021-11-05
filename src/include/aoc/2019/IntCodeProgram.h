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
        ADD                  = 1,
        MULTIPLY             = 2,
        READ                 = 3,
        WRITE                = 4,
        JUMP_IF_TRUE         = 5,
        JUMP_IF_FALSE        = 6,
        LESS_THAN            = 7,
        EQUALS               = 8,
        ADJUST_RELATIVE_BASE = 9,
    };

    enum class ParameterMode
    {
        POSITION  = 0,
        IMMEDIATE = 1,
        RELATIVE  = 2,
    };

    class Program
    {
    public:
        Program(std::istream& stream)
            : _code(
                ranges::getlines(stream, ',')
                    | ranges::views::transform([](auto&& s) { return std::stoll(s); })
                    | ranges::to_vector
            )
        {}

        auto begin() { return _code.begin(); }
        auto end()   { return _code.end(); }
        std::size_t size() const { return _code.size(); }
        long long& operator[](std::size_t idx)
        {
            if (idx >= _code.size())
            {
                _code.resize(idx + 1);
            }
            return _code[idx];
        }

    private:
        std::vector<long long> _code;
    };

    static std::tuple<Operation, ParameterMode, ParameterMode, ParameterMode> splitOpCode(long long value)
    {
        return std::tuple{
            static_cast<Operation>(value % 100),
            static_cast<ParameterMode>((value % 1000) / 100),
            static_cast<ParameterMode>((value % 10000) / 1000),
            static_cast<ParameterMode>((value % 100000) / 10000),
        };
    }

public:
    explicit IntCodeProgram(std::istream& stream)
        : _program(stream)
    {}

    long long operator()(long long noun, long long verb) const
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

    std::pair<long long, bool> operator()(long long input)
    {
        return (*this)(std::vector{input});
    }

    std::pair<long long, bool> operator()(const std::vector<long long>& inputs)
    {
        auto value = [&](std::size_t idx, ParameterMode mode) -> long long&
        {
            switch (mode)
            {
                case ParameterMode::POSITION:  return _program[_program[idx]];
                case ParameterMode::IMMEDIATE: return _program[idx];
                case ParameterMode::RELATIVE:  return _program[_relativeBase + _program[idx]];
            }
            throw std::runtime_error{"invalid mode"};
        };

        long long output = 0;
        std::size_t inputIdx = 0;
        while (idx < _program.size() && _program[idx] != 99)
        {
            const auto[op, m1, m2, m3] = splitOpCode(_program[idx++]);
            switch (op)
            {
                case Operation::READ:
                    if (inputIdx >= inputs.size())
                    {
                        --idx;
                        return {output, false};
                    }
                    value(idx++, m1) = inputs.at(inputIdx++);
                    break;
                case Operation::WRITE:
                    output = value(idx++, m1);
                    break;
                case Operation::ADD:
                case Operation::MULTIPLY:
                case Operation::LESS_THAN:
                case Operation::EQUALS:
                {
                    const auto a = value(idx++, m1);
                    const auto b = value(idx++, m2);
                    value(idx++, m3) = exec(op, a, b);
                    break;
                }
                case Operation::JUMP_IF_TRUE:
                case Operation::JUMP_IF_FALSE:
                {
                    if ((value(idx++, m1) != 0) ^ (op == Operation::JUMP_IF_FALSE))
                    {
                        idx = value(idx, m2);
                    }
                    else
                    {
                        ++idx;
                    }
                    break;
                }
                case Operation::ADJUST_RELATIVE_BASE:
                    _relativeBase += value(idx++, m1);
                    break;
            }
        }
        return std::pair{output, true};
    }

private:
    static long long exec(Operation op, long long a, long long b)
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
    Program _program;
    std::size_t idx = 0;
    std::size_t _relativeBase = 0;
};

}

#endif //ADVENTOFCODE_INTCODEPROGRAM_H
