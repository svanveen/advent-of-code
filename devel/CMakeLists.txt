### library ###
add_library(current EXCLUDE_FROM_ALL
    ${CMAKE_SOURCE_DIR}/src/lib/src/${CMAKE_PROJECT_VERSION_MAJOR}/exercise${CMAKE_PROJECT_VERSION_PATCH}.cpp
)

add_library(${PROJECT_NAME}::current ALIAS current)


target_include_directories(current
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/lib/include>
)

target_link_libraries(current
    PUBLIC
        CONAN_PKG::range-v3
)

target_compile_features(current
    PUBLIC
        cxx_std_17
)

### executable ###
configure_file(
    include/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/Config.h
)

add_executable(current-exercise EXCLUDE_FROM_ALL
    src/main.cpp
)

target_link_libraries(current-exercise
    PRIVATE
        ${PROJECT_NAME}::current
        CONAN_PKG::docopt.cpp
)

target_include_directories(current-exercise
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

### test ###
add_executable(current-test EXCLUDE_FROM_ALL
    ${CMAKE_SOURCE_DIR}/test/src/${CMAKE_PROJECT_VERSION_MAJOR}/exercise${CMAKE_PROJECT_VERSION_PATCH}.cpp
)

target_include_directories(current-test
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test/include>
)

target_link_libraries(current-test
    PRIVATE
        ${PROJECT_NAME}::current
        CONAN_PKG::gtest
)

add_test(current-test current-test)
