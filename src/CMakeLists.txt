add_executable(advent-of-code src/main.cpp)

target_link_libraries(advent-of-code
    PRIVATE
        CONAN_PKG::docopt.cpp
)

add_library(aoc INTERFACE)
add_library(${PROJECT_NAME}::aoc ALIAS aoc)

target_include_directories(aoc
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/gen/include
)

target_link_libraries(aoc INTERFACE CONAN_PKG::range-v3)

target_compile_features(aoc INTERFACE cxx_std_17)

foreach(EXERCISE RANGE 1 25)
    add_exercise(2020 ${EXERCISE} OBJECT_TARGET)

    target_sources(advent-of-code PRIVATE $<TARGET_OBJECTS:${OBJECT_TARGET}>)
    target_link_libraries(advent-of-code PRIVATE ${OBJECT_TARGET})
endforeach()

install(TARGETS advent-of-code
    RUNTIME DESTINATION bin COMPONENT Runtime
)
