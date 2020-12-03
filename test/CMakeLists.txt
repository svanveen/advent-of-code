enable_testing()

add_executable(advent-of-code-test test.cpp)

target_include_directories(advent-of-code-test
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(advent-of-code-test
    PRIVATE
        CONAN_PKG::gtest
        CONAN_PKG::range-v3
)

target_compile_features(advent-of-code-test
    PRIVATE
        cxx_std_17
)

install(TARGETS advent-of-code-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(advent-of-code-test advent-of-code-test)
