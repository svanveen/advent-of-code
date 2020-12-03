add_executable(advent-of-code main.cpp)

target_include_directories(advent-of-code
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(advent-of-code
    PRIVATE
        CONAN_PKG::docopt.cpp
        CONAN_PKG::range-v3
)

target_compile_features(advent-of-code
    PRIVATE
        cxx_std_17
)
