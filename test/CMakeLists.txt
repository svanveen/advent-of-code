enable_testing()

add_library(aoc-test INTERFACE)
add_library(${PROJECT_NAME}::aoc-test ALIAS aoc-test)

target_link_libraries(aoc-test
    INTERFACE
        ${PROJECT_NAME}::aoc
        CONAN_PKG::gtest
)

file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}/res/" "${CMAKE_SOURCE_DIR}/res/*/*.dat")
foreach(RESOURCE IN LISTS RESOURCES)
    get_filename_component(YEAR ${RESOURCE} DIRECTORY)
    get_filename_component(EXERCISE ${RESOURCE} NAME_WE)

    add_exercise_test(${YEAR} ${EXERCISE})
endforeach()
