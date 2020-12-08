#include <string>
#include <vector>
#include <range/v3/action.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

struct Instruction
{
    enum class Operation
    {
        ACC,
        JMP,
        NOP,
    } operation;
    int argument;

    static Instruction parse(const std::string& str)
    {
        std::smatch match;
        std::regex_match(str, match, std::regex{R"((acc|jmp|nop) ([+-]\d+))"});

        static const std::map<std::string, Operation> operations
        {
            {"acc", Operation::ACC},
            {"jmp", Operation::JMP},
            {"nop", Operation::NOP},
        };

        return {operations.at(match[1]), std::stoi(match[2])};
    }

    void flip()
    {
        if (Operation::JMP == operation)
        {
            operation = Operation::NOP;
        }
        else if (Operation::NOP == operation)
        {
            operation = Operation::JMP;
        }

    }
};

template <typename INSTRUCTIONS>
auto runInstructions(INSTRUCTIONS&& instructions)
{
    auto visited = ranges::views::repeat_n(false, instructions.size()) | ranges::to_vector;

    std::size_t idx = 0;
    int accumulator = 0;
    for (; !visited[idx] && idx < instructions.size();)
    {
        visited[idx] = true;
        const auto&[op, arg] = instructions[idx];
        switch (op)
        {
            case Instruction::Operation::ACC:
            {
                accumulator += arg;
                ++idx;
                break;
            }
            case Instruction::Operation::JMP:
            {
                idx += arg;
                break;
            }
            case Instruction::Operation::NOP:
            {
                ++idx;
                break;
            }
        }
    }
    return std::make_pair(idx, accumulator);
}

auto getInstrucions(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(Instruction::parse)
        | ranges::to_vector;
}

}

template <>
std::size_t exercise<2020, 8, 1>(std::istream& stream)
{
    const auto instructions = getInstrucions(stream);
    return runInstructions(instructions).second;
}

template <>
std::size_t exercise<2020, 8, 2>(std::istream& stream)
{
    const auto instructions = getInstrucions(stream);

    auto values = ranges::views::iota(0u, instructions.size())
        | ranges::views::filter([&](auto&& idx) { return instructions[idx].operation != Instruction::Operation::ACC; })
        | ranges::views::transform([&](auto&& idx)
            {
                auto i = instructions; // TODO: prevent this copies
                i[idx].flip();
                return i;
            })
        | ranges::views::transform([](auto&& instr) { return runInstructions(instr); })
        | ranges::views::filter([&](auto&& result) { return result.first == instructions.size(); })
        | ranges::views::values;
    return ranges::front(values);
}

}
