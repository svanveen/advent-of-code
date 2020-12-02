#include <iostream>
#include <day01.h>
#include <day02.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "path argument missing\n";
        return 1;
    }
    const auto path = std::string{argv[1]};

    std::cout << "Solutions day 1" << std::endl;
    std::cout << "Exercise 1: " << day1::exercise1(path) << std::endl;
    std::cout << "Exercise 2: " << day1::exercise2(path) << std::endl;

    std::cout << "Solutions day 2" << std::endl;
    std::cout << "Exercise 1: " << day2::exercise1(path) << std::endl;
    std::cout << "Exercise 2: " << day2::exercise2(path) << std::endl;
}