#ifndef ADVENTOFCODE_RESULT_H
#define ADVENTOFCODE_RESULT_H

#include <cstdint>
#include <iostream>
#include <string>
#include <variant>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

class Result
{
public:
    Result(std::size_t value)
        : data(value)
    {}

    Result(std::string value)
        : data(std::move(value))
    {}

    friend inline bool operator==(size_t lhs, const Result& rhs)
    {
        return std::visit(utils::overloaded{
            [&](size_t value) { return lhs == value; },
            [](const std::string&) { return false; }
        }, rhs.data);
    }

    friend inline bool operator==(const std::string& lhs, const Result& rhs)
    {
        return std::visit(utils::overloaded{
            [](size_t) { return false; },
            [&](const std::string& value) { return lhs == value; }
        }, rhs.data);
    }

    friend inline std::ostream& operator<<(std::ostream& os, const Result& result)
    {
      std::visit([&os](const auto& result) { os << result; }, result.data);
      return os;
    }

private:
    std::variant<std::size_t, std::string> data;
};

}

#endif // ADVENTOFCODE_RESULT_H
