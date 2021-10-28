#include <regex>
#include <string>
#include <variant>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <aoc/utils/Overloaded.h>

namespace aoc
{

namespace
{

using Int = std::size_t;
using Block = std::monostate;

using Operation = std::variant<std::plus<>, std::multiplies<>>;

struct OpeningBrace{};
struct ClosingBrace{};

using Token = std::variant<Int, Operation, OpeningBrace, ClosingBrace>;

struct UnevaluatedOperation
{
    Int operator()()
    {
        return std::visit([&](auto&& op) { return op(lhs, rhs); }, operation);
    }

    Int lhs;
    Int rhs;
    Operation operation;
};

using Value = std::variant<Int, UnevaluatedOperation>;

template <typename PRECEDENCE>
struct LBoundOperator
{
    LBoundOperator(const Value& value, const Operation& opertion)
        : value(std::visit(
            utils::overloaded{
                [](Int value) -> Value { return value; },
                [&](UnevaluatedOperation unevaluatedOperation) -> Value {
                    return (unevaluatedOperation.operation.index() == opertion.index()) ? Value{unevaluatedOperation()} : Value{unevaluatedOperation};
                }
            }, value)
        )
        , operation(opertion)
    {}

    Value operator()(Int other)
    {
        return std::visit([&](auto&& value) { return eval(value, other); }, value);
    }

    Value eval(Int value, Int other)
    {
        return std::visit([&](auto&& op) -> Value
            {
                if (std::is_same_v<PRECEDENCE, void> || std::is_same_v<PRECEDENCE, std::decay_t<decltype(op)>>)
                {
                    return op(value, other);
                }
                else
                {
                    return UnevaluatedOperation{value, other, operation};
                }
            }, operation);
    }

    Value eval(UnevaluatedOperation unevaluatedOperation, Int other)
    {
        unevaluatedOperation.rhs = std::visit([&](auto&& op) { return op(unevaluatedOperation.rhs, other); }, operation);
        return unevaluatedOperation;
    }

    Value value;
    Operation operation;
};

template <typename PRECEDENCE>
using Expression = std::variant<Block, Value, LBoundOperator<PRECEDENCE>>;

template <typename PRECEDENCE>
struct Evaluator
{
    Evaluator()
        : expressions({Block{}})
    {}

    Int getValue() const
    {
        if (expressions.size() == 1 && std::holds_alternative<Value>(expressions.top()))
        {
            return std::visit(
                utils::overloaded{
                    [](Int value) { return value; },
                    [](UnevaluatedOperation unevaluatedOperation) { return unevaluatedOperation(); }
                }, std::get<Value>(expressions.top())
            );
        }
        throw std::runtime_error{"invalid end state"};
    }

    void operator()(const Token& token)
    {
        std::visit(*this, expressions.top(), token);
    }

    void operator()(Block, Int value)
    {
        expressions.top() = value;
    }

    void operator()(LBoundOperator<PRECEDENCE> lBoundOperator, Int value)
    {
        expressions.top() = lBoundOperator(value);
    }

    void operator()(LBoundOperator<PRECEDENCE>, OpeningBrace)
    {
        expressions.push(Block{});
    }

    void operator()(Value value, Operation operation)
    {
        expressions.top() = LBoundOperator<PRECEDENCE>{value, operation};
    }

    void operator()(Value value, ClosingBrace)
    {
        expressions.pop();
        std::visit(utils::overloaded{
            [this](auto&& top, Int value) { return (*this)(top, value); },
            [this](auto&& top, UnevaluatedOperation unevaluatedOperation) { return (*this)(top, unevaluatedOperation()); }
        }, expressions.top(), value);
    }

    void operator()(Operation, OpeningBrace)
    {
        expressions.push(Block{});
    }

    void operator()(Block, OpeningBrace)
    {
        expressions.push(Block{});
    }

    template <typename T, typename S>
    void operator()(T, S) { throw std::runtime_error{"invalid token"}; }

private:
    std::stack<Expression<PRECEDENCE>> expressions;
};

template <typename PRECEDENCE>
auto compute(const std::string& str)
{
    auto parseToken = [](auto&& part) -> Token
    {
        switch (*part.first)
        {
            case '+': return std::plus<>{};
            case '*': return std::multiplies<>{};
            case '(': return OpeningBrace{};
            case ')': return ClosingBrace{};
            default:  return std::stoi(part);
        }
    };

    auto tokens = str
        | ranges::views::tokenize(std::regex{R"((\d+|[*+()]))"})
        | ranges::views::transform(parseToken);

    Evaluator<PRECEDENCE> evaluator;
    for (auto&& token : tokens)
    {
        evaluator(token);
    }

    return evaluator.getValue();
}

template <typename PRECEDENCE=void>
auto exercise(std::istream& stream)
{
    auto results = ranges::getlines(stream)
        | ranges::views::transform([](auto&& expression) { return compute<PRECEDENCE>(expression); });
    return ranges::accumulate(results, std::size_t{0});
}

}

template <>
Result exercise<2020, 18, 1>(std::istream& stream)
{
    return exercise<>(stream);
}

template <>
Result exercise<2020, 18, 2>(std::istream& stream)
{
    return exercise<std::plus<>>(stream);
}

}
