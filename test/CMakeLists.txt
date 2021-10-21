enable_testing()

add_library(aoc-test INTERFACE)
add_library(${PROJECT_NAME}::aoc-test ALIAS aoc-test)

target_link_libraries(aoc-test
    INTERFACE
        ${PROJECT_NAME}::aoc
        CONAN_PKG::gtest
)

foreach(EXERCISE RANGE 1 25)
    add_exercise_test(2020 ${EXERCISE} OBJECT_TARGET)
endforeach()
