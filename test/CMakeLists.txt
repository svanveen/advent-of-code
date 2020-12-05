enable_testing()

add_executable(advent-of-code-test
    src/exercise01.cpp
    src/exercise02.cpp
    src/exercise03.cpp
    src/exercise04.cpp
    src/exercise05.cpp
)

target_include_directories(aoc
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(advent-of-code-test
    PRIVATE
        AdventOfCode::aoc
        CONAN_PKG::gtest
)

install(TARGETS advent-of-code-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(advent-of-code-test advent-of-code-test)
