#include <gtest/gtest.h>
#include <aoc/exercise.h>
#include <aoc/res/2020/Data-21.h>

constexpr auto input = R"(mxmxvkd kfcds sqjhc nhms (contains dairy, fish)
trh fvjkl sbzzf mxmxvkd (contains dairy)
sqjhc fvjkl (contains soy)
sqjhc mxmxvkd sbzzf (contains fish)
)";

TEST(Exercise21, Part1)
{
    EXPECT_EQ(5, (aoc::exercise<2020, 21, 1>(input)));
    EXPECT_EQ(2389, (aoc::exercise<2020, 21, 1>(aoc::res::data_2020_21)));
}

TEST(Exercise21, Part2)
{
    EXPECT_EQ("mxmxvkd,sqjhc,fvjkl", (aoc::exercise<2020, 21, 2>(input)));
    EXPECT_EQ("fsr,skrxt,lqbcg,mgbv,dvjrrkv,ndnlm,xcljh,zbhp", (aoc::exercise<2020, 21, 2>(aoc::res::data_2020_21)));
}
