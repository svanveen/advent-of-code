enable_testing()

add_executable(advent-of-code-test test.cpp)

target_link_libraries(advent-of-code-test
    PRIVATE
        AdventOfCode::aoc
        CONAN_PKG::gtest
)

install(TARGETS advent-of-code-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(advent-of-code-test advent-of-code-test)
