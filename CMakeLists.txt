cmake_minimum_required(VERSION 3.15)
project(AdventOfCode VERSION 2020.12.25)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x600)
endif()

add_subdirectory(src)

add_subdirectory(test)

add_subdirectory(devel)


install(DIRECTORY ${CMAKE_SOURCE_DIR}/res/ DESTINATION share)
