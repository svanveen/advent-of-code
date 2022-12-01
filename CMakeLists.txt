cmake_minimum_required(VERSION 3.17)
project(AdventOfCode VERSION 2021.14)

set(CMAKE_EXPORT_COMPILE_DATABASE ON)

include(cmake/GenerateExercise.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x600)
endif()

add_subdirectory(src)

add_subdirectory(test)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/res/ DESTINATION share)
