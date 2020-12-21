#include <regex>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercises.h>
#include <range/v3/iterator_range.hpp>

namespace aoc
{

namespace
{

struct Food
{
    std::vector<std::string> ingredients;
    std::vector<std::string> allergens;
};

auto parse(const std::string& str)
{
    static const std::regex regex{R"((\w+(?: \w+)*) \(contains (\w+(?:, \w+)*)\))"};
    std::smatch match;
    if (!std::regex_match(str, match, regex))
    {
        throw std::runtime_error{"parse error"};
    }
    auto ingredients = ranges::make_iterator_range(match[1].first, match[1].second)
        | ranges::views::tokenize(std::regex{R"(\w+)"})
        | ranges::views::transform([](auto&& token) { return token.str(); })
        | ranges::to_vector
        | ranges::actions::sort;

    auto allergens = ranges::make_iterator_range(match[2].first, match[2].second)
        | ranges::views::tokenize(std::regex{R"(\w+)"})
        | ranges::views::transform([](auto&& token) { return token.str(); })
        | ranges::to_vector
        | ranges::actions::sort;

    return Food{std::move(ingredients), std::move(allergens)};
}

}

template <>
std::size_t exercise<2020, 21, 1>(std::istream& stream)
{
    auto foods = ranges::getlines(stream)
        | ranges::views::transform(parse)
        | ranges::to_vector;

    auto ingredients = foods
        | ranges::views::transform([](auto&& food) { return food.ingredients; })
        | ranges::actions::join
        | ranges::actions::sort
        | ranges::actions::unique;

    auto intersect = [&](auto&& group)
    {
        return ranges::accumulate(group | ranges::views::values, ingredients, [](auto&& lhs, auto&& rhs)
        {
            return ranges::views::set_intersection(lhs, rhs) | ranges::to_vector;
        });
    };

    auto allergenToIngredients = foods
        | ranges::views::transform([](auto&& food) { return food.allergens | ranges::views::transform([&](auto&& allergen) { return std::pair{allergen, food.ingredients}; }); })
        | ranges::actions::join
        | ranges::actions::sort([](auto&& lhs, auto&& rhs) { return lhs.first < rhs.first; });

    auto ingredientsWithAllergens = allergenToIngredients
        | ranges::views::group_by([](auto&& lhs, auto&& rhs) { return lhs.first == rhs.first; })
        | ranges::views::transform(intersect)
        | ranges::actions::join
        | ranges::actions::sort
        | ranges::actions::unique;

    auto countOccurences = [&](auto&& ingredient)
    {
        auto count = [&](auto&& food) { return ranges::count(food.ingredients, ingredient); };
        return ranges::accumulate(foods, 0, std::plus<>{}, count);
    };

    auto ingredientsWithoutAllergens = ranges::views::set_difference(ingredients, ingredientsWithAllergens);
    return ranges::accumulate(ingredientsWithoutAllergens, 0, std::plus<>{}, countOccurences);
}

template <>
std::size_t exercise<2020, 21, 2>(std::istream& stream)
{
    return 0;
}

}
