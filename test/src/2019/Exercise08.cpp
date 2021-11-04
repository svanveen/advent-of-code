#include <gtest/gtest.h>
#include <aoc/Exercise.h>
#include <aoc/res/2019/Data-08.h>

using namespace std::string_literals;

TEST(Exercise8, Part1)
{
    EXPECT_EQ(1806, (aoc::exercise<2019, 8, 1>(aoc::res::data_2019_08)));
}

TEST(Exercise8, Part2)
{
    const auto expectation = R"(
  ##  ##  #### ###   ##  
   # #  # #    #  # #  # 
   # #  # ###  #  # #  # 
   # #### #    ###  #### 
#  # #  # #    # #  #  # 
 ##  #  # #    #  # #  # )"s;
    EXPECT_EQ(expectation, (aoc::exercise<2019, 8, 2>(aoc::res::data_2019_08)));
}
