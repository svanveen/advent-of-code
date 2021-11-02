#include <regex>
#include <sstream>
#include <string>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator_range.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <aoc/exercise.h>

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

auto getFoods(std::istream& stream)
{
    return ranges::getlines(stream)
        | ranges::views::transform(parse)
        | ranges::to_vector;
}

auto getIngredients(const std::vector<Food>& foods)
{
    return foods
        | ranges::views::transform([](auto&& food) { return food.ingredients; })
        | ranges::actions::join
        | ranges::actions::sort
        | ranges::actions::unique;
}

auto getAllergenIngredientOptionsMapping(const std::vector<Food>& foods, const std::vector<std::string>& ingredients)
{
    auto intersect = [&](auto&& group)
    {
        return std::pair{
            group.front().first,
            ranges::accumulate(group | ranges::views::values, ingredients, [](auto&& lhs, auto&& rhs)
            {
                return ranges::views::set_intersection(lhs, rhs) | ranges::to_vector;
            })
        };
    };

    auto allergenToIngredients = foods
        | ranges::views::transform([](auto&& food) { return food.allergens | ranges::views::transform([&](auto&& allergen) { return std::pair{allergen, food.ingredients}; }); })
        | ranges::actions::join
        | ranges::actions::sort([](auto&& lhs, auto&& rhs) { return lhs.first < rhs.first; });

    return allergenToIngredients
        | ranges::views::group_by([](auto&& lhs, auto&& rhs) { return lhs.first == rhs.first; })
        | ranges::views::transform(intersect)
        | ranges::to_vector;
}

}

template <>
Result exercise<2020, 21, 1>(std::istream& stream)
{
    const auto foods = getFoods(stream);
    const auto ingredients = getIngredients(foods);

    auto allergenIngredientMapping = getAllergenIngredientOptionsMapping(foods, ingredients);

    auto ingredientsWithAllergens = allergenIngredientMapping
        | ranges::views::values
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
Result exercise<2020, 21, 2>(std::istream& stream)
{
    const auto foods = getFoods(stream);
    const auto ingredients = getIngredients(foods);

    std::map<std::string, bool> isSet;
    std::map<std::string, std::string> allergenToIngredients;

    auto allergenIngredientOptionsMapping = getAllergenIngredientOptionsMapping(foods, ingredients)
        | ranges::actions::sort([](auto&& lhs, auto&& rhs) { return lhs.second.size() < rhs.second.size(); });

    while (allergenToIngredients.size() != allergenIngredientOptionsMapping.size())
    {
        for (auto&& allergenIngredientOptions : allergenIngredientOptionsMapping)
        {
            auto unsetIngredients = allergenIngredientOptions.second | ranges::views::filter([&](auto&& ingredient) { return !isSet[ingredient]; });
            if (ranges::distance(unsetIngredients) == 1)
            {
                const auto& ingredient = unsetIngredients.front();
                allergenToIngredients[allergenIngredientOptions.first] = ingredient;
                isSet[ingredient] = true;
            }
        }
    }

    auto ingredientsWithAllergen = allergenToIngredients | ranges::views::values;

    return [&]()
    {
        auto sstream = std::stringstream{};
        std::copy(ingredientsWithAllergen.begin(), ingredientsWithAllergen.end(), std::ostream_iterator<std::string>{sstream, ","});
        auto result = sstream.str();
        result.pop_back();
        return result;
    }();
}

}
