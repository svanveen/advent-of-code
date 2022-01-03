#include <functional>
#include <regex>
#include <sstream>
#include <variant>
#include <vector>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

namespace {

template <char SYMBOL>
struct OperationT
{
    int operator()(int lhs, int rhs) const
    {
        if constexpr (SYMBOL == '+')
        { return lhs + rhs; }
        else if constexpr (SYMBOL == '*')
        { return lhs * rhs; }
        else if constexpr (SYMBOL == '/')
        { return lhs / rhs; }
        else if constexpr (SYMBOL == '%')
        { return lhs % rhs; }
        else if constexpr (SYMBOL == '=')
        { return lhs == rhs; }
    }
};

template <char SYMBOL>
std::ostream& operator<<(std::ostream& stream, const OperationT<SYMBOL>& operation)
{
    return stream << ' ' << SYMBOL << ' ';
}

std::ostream& operator<<(std::ostream& stream, const OperationT<'='>& operation)
{
    return stream << " == ";
}

using Operation = std::variant
        <
                OperationT<'+'>,
                OperationT<'*'>,
                OperationT<'/'>,
                OperationT<'%'>,
                OperationT<'='>
        >;

class Term
{
public:
    Term() = default;

    Term(int value)
            : data(value)
    {
    }

    Term(std::string term)
            : data(std::move(term))
    {
    }

public:
    Term& operator+=(const Term& other)
    {
        return exec(other, OperationT<'+'>{});
    }

    Term& operator*=(const Term& other)
    {
        return exec(other, OperationT<'*'>{});
    }

    Term& operator/=(const Term& other)
    {
        return exec(other, OperationT<'/'>{});
    }

    Term& operator%=(const Term& other)
    {
        return exec(other, OperationT<'%'>{});
    }

    Term& operator==(const Term& other)
    {
        return exec(other, OperationT<'='>{});
    }

private:
    Term& exec(const Term& other, const Operation& operation)
    {
        return *this = std::visit
                (
                        utils::overloaded
                                {
                                        [&](const auto& op, int lhs, int rhs) -> Term { return op(lhs, rhs); },
                                        [&](const OperationT<'+'>& op, int lhs, const std::string& rhs) -> Term { return plus0(lhs, rhs); },
                                        [&](const OperationT<'+'>& op, const std::string& lhs, int rhs) -> Term { return plus0(rhs, lhs); },
                                        [&](const OperationT<'*'>& op, int lhs, const std::string& rhs) -> Term { return multBy0(lhs, rhs); },
                                        [&](const OperationT<'*'>& op, const std::string& lhs, int rhs) -> Term { return multBy0(rhs, lhs); },
                                        [&](const OperationT<'/'>& op, const std::string& lhs, int rhs) -> Term { return divBy1(lhs, rhs); },
                                        [&](const OperationT<'='>& op, int lhs, const std::string& rhs) -> Term { return eq0(rhs, lhs); },
                                        [&](const OperationT<'='>& op, const std::string& lhs, int rhs) -> Term { return eq0(lhs, rhs); },
                                        [&](const auto& op, const auto& lhs, const auto& rhs) -> Term { return constructTermString(op, lhs, rhs); }
                                },
                        operation, data, other.data
                );
    }

    static Term plus0(int lhs, const std::string& rhs)
    {
        if (lhs == 0)
        {
            return rhs;
        }
        return constructTermString(OperationT<'+'>{}, lhs, rhs);
    }

    static Term multBy0(int lhs, const std::string& rhs)
    {
        if (lhs == 0)
        {
            return 0;
        }
        return constructTermString(OperationT<'*'>{}, lhs, rhs);
    }

    static Term divBy1(const std::string& lhs, int rhs)
    {
        if (rhs == 1)
        {
//            return lhs;
        }
        return constructTermString(OperationT<'/'>{}, lhs, rhs);
    }

    static Term eq0(const std::string& lhs, int rhs)
    {
        if (rhs == 0)
        {
            return '!' + lhs;
        }
        return constructTermString(OperationT<'='>{}, lhs, rhs);
    }

    static Term constructTermString(const Operation& operation, const Term& lhs, const Term& rhs)
    {
        return std::visit
        (
            utils::overloaded
            {
                [&](const OperationT<'='>& op, const auto& lhs, const auto& rhs) -> Term {
                    auto stream = std::stringstream{};
                    stream << '(' << lhs << op << rhs << ')';
                    return stream.str();
                },
                [&](const OperationT<'+'>& op, const auto& lhs, const auto& rhs) -> Term {
                    auto stream = std::stringstream{};
                    stream << '(' << lhs << op << rhs << ')';
                    return stream.str();
                },
                [&](const auto& op, const auto& lhs, const auto& rhs) -> Term {
                    auto stream = std::stringstream{};
                    stream << lhs << op << rhs;
                    return stream.str();
                }
            },
            operation, lhs.data, rhs.data
        );
    }

    friend std::ostream& operator<<(std::ostream& stream, const Term& term)
    {
        std::visit([&stream](const auto& t) { stream << t; }, term.data);
        return stream;
    }

private:
    std::variant<int, std::string> data = 0;
};

void terms(std::istream& stream)
{
    Term w = {};
    Term x = {};
    Term y = {};
    Term z = {};
    Term tmp = {};
    const auto ref = [&](const std::string& str, bool fallbackOnValue = false) -> Term& {
        switch (str.front())
        {
            case 'w':
                return w;
            case 'x':
                return x;
            case 'y':
                return y;
            case 'z':
                return z;
            default:
                if (fallbackOnValue)
                {
                    tmp = std::stoi(str);
                    return tmp;
                }
        }
        throw std::runtime_error{"could not parse variable"};
    };

    const auto value = [&](const std::string& str) {
        return ref(str, true);
    };

    auto idx = std::size_t{};
    for (const auto& line : ranges::getlines(stream))
    {
        {
            const auto regex = std::regex{R"(^inp ([a-z])$)"};
            auto match = std::smatch{};
            if (std::regex_match(line, match, regex))
            {
                if (idx > 0)
                {
                    std::cout << 'z' << std::to_string(idx) << " = " << z << ";\n";

                    w = "w" + std::to_string(idx);
                    x = "x" + std::to_string(idx);
                    y = "y" + std::to_string(idx);
                    z = "z" + std::to_string(idx);
                }

                auto& a = ref(match[1]);
                a = "input[" + std::to_string(idx++) + ']';
                continue;
            }
        }
        {
            const auto regex = std::regex{R"(^(add|mul|div|mod|eql) ([a-z]) ([a-z]|-?\d+)$)"};
            auto match = std::smatch{};
            if (std::regex_match(line, match, regex))
            {
                const auto operation = match[1].str();
                auto& a = ref(match[2]);
                auto& b = ref(match[3], true);
                if (operation == "add")
                {
                    a += b;
                }
                else if (operation == "mul")
                {
                    a *= b;
                }
                else if (operation == "div")
                {
                    a /= b;
                }
                else if (operation == "mod")
                {
                    a %= b;
                }
                else if (operation == "eql")
                {
                    a = (a == b);
                }
                else
                {
                    throw std::runtime_error{"could not parse operation"};
                }
            }
        }
    }
    std::cout << 'z' << std::to_string(idx) << " = " << z << ";\n";
}

}

template <>
Result exercise<2021, 24, 1>(std::istream& stream)
{
    terms(stream);

    // calculation is done by hand based on the output of the above function call
    return 49917929934999;
}

template <>
Result exercise<2021, 24, 2>(std::istream& stream)
{
    // calculation is done by hand based on the output of the above function call
    return 11911316711816;
}

}
