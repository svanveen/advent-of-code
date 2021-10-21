#include <gtest/gtest.h>
#include <aoc/exercises.h>

constexpr auto input = R"(mxmxvkd kfcds sqjhc nhms (contains dairy, fish)
trh fvjkl sbzzf mxmxvkd (contains dairy)
sqjhc fvjkl (contains soy)
sqjhc mxmxvkd sbzzf (contains fish)
)";

TEST(Exercise21, Part1)
{
    EXPECT_EQ(5, (aoc::exercise<2020, 21, 1>(input)));
}

