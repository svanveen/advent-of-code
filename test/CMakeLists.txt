enable_testing()

add_library(aoc-test INTERFACE)
add_library(${PROJECT_NAME}::aoc-test ALIAS aoc-test)

target_include_directories(aoc-test
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(aoc-test
    INTERFACE
        ${PROJECT_NAME}::aoc
        CONAN_PKG::gtest
)

add_subdirectory(src/2020)
