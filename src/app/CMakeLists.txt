add_executable(advent-of-code main.cpp)

target_link_libraries(advent-of-code
    PRIVATE
        ${PROJECT_NAME}::aoc
        CONAN_PKG::docopt.cpp
)

target_compile_features(advent-of-code
    PRIVATE
        cxx_std_17
)

install(TARGETS advent-of-code
    RUNTIME DESTINATION bin COMPONENT Runtime
)
