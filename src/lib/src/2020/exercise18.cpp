#include <regex>
#include <string>
#include <variant>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>

namespace aoc
{

namespace
{

using Operation = std::variant<std::plus<>, std::multiplies<>>;

struct OpeningBrace{};
struct ClosingBrace{};

using Token = std::variant<std::size_t, Operation, OpeningBrace, ClosingBrace>;

struct LBoundOperator
{
    std::size_t operator()(std::size_t other)
    {
        std::cout << value << 'x' << other << std::endl;
        return std::visit([&](auto&& op) { return op(value, other); }, operation);
    }

    std::size_t value;
    Operation operation;
};

using Expression = std::variant<std::monostate, std::size_t, LBoundOperator>;

struct Evaluator
{
    Evaluator()
        : expressions({std::monostate{}})
    {}

    virtual ~Evaluator() = default;

    virtual std::size_t getValue()
    {
        if (expressions.size() == 1 && std::holds_alternative<std::size_t>(expressions.top()))
        {
            return std::get<std::size_t>(expressions.top());
        }
        throw std::runtime_error{"invalid end state"};
    }

    void operator()(const Token& token)
    {
        std::visit(*this, expressions.top(), token);
    }

    void operator()(std::monostate, std::size_t value)
    {
        expressions.top() = value;
    }

    void operator()(LBoundOperator lBoundOperator, std::size_t value)
    {
        expressions.top() = lBoundOperator(value);
    }

    void operator()(LBoundOperator, OpeningBrace)
    {
        expressions.push(std::monostate{});
    }

    virtual void operator()(std::size_t value, Operation operation)
    {
        expressions.top() = LBoundOperator{value, operation};
    }

    void operator()(std::size_t value, ClosingBrace)
    {
        expressions.pop();
        std::visit([&](auto&& top) { return (*this)(top, value); }, expressions.top());
    }

    void operator()(Operation, OpeningBrace)
    {
        expressions.push(std::monostate{});
    }

    void operator()(std::monostate, OpeningBrace)
    {
        expressions.push(std::monostate{});
    }

    void operator()(std::size_t, std::size_t)     { throw std::runtime_error{"invalid token"}; }
    void operator()(std::size_t, OpeningBrace)    { throw std::runtime_error{"invalid token"}; }
    void operator()(std::monostate, Operation)    { throw std::runtime_error{"invalid token"}; }
    void operator()(std::monostate, ClosingBrace) { throw std::runtime_error{"invalid token"}; }
    void operator()(LBoundOperator, Operation)    { throw std::runtime_error{"invalid token"}; }
    void operator()(LBoundOperator, ClosingBrace) { throw std::runtime_error{"invalid token"}; }

protected:
    std::stack<Expression> expressions;
};

struct Evaluator2 : public Evaluator
{
    std::size_t getValue() override
    {
        while (expressions.size() > 1)
        {
            if (!std::holds_alternative<std::size_t>(expressions.top()))
            {
                throw std::runtime_error{"invalid end state"};
            }
            const auto value = std::get<std::size_t>(expressions.top());
            expressions.pop();
            std::visit([&](auto&& top) { return (*this)(top, value); }, expressions.top());
        }
        if (!std::holds_alternative<std::size_t>(expressions.top()))
        {
            throw std::runtime_error{"invalid end state"};
        }
        return std::get<std::size_t>(expressions.top());
    }

    using Evaluator::operator();

    void operator()(std::size_t value, Operation operation) override
    {
        expressions.top() = LBoundOperator{value, operation};
        if (std::holds_alternative<std::multiplies<>>(operation))
        {
            expressions.push(std::monostate{});
        }
    }
};

template <typename EVALUATOR>
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

    EVALUATOR evaluator;
    for (auto&& token : tokens)
    {
        evaluator(token);
    }

    return evaluator.getValue();
}

}

template <>
std::size_t exercise<2020, 18, 1>(std::istream& stream)
{
    auto results = ranges::getlines(stream)
        | ranges::views::transform([](auto&& str) { return compute<Evaluator>(str); });
    return ranges::accumulate(results, std::size_t{0});
}

template <>
std::size_t exercise<2020, 18, 2>(std::istream& stream)
{
    auto results = ranges::getlines(stream)
       | ranges::views::transform([](auto&& str) { return compute<Evaluator2>(str); });
    for (auto&& r : results)
    {
        std::cout << "R=" << r << std::endl;
    }
    return ranges::accumulate(results, std::size_t{0});
}

}
