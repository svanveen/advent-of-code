cmake_minimum_required(VERSION 3.16)
project(AdventOfCode VERSION 2020.12.3)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x600)
endif()

add_subdirectory(src)

add_subdirectory(test)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(TARGETS advent-of-code
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib COMPONENT Development
    LIBRARY DESTINATION lib COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)

install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(FILES
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/res/ DESTINATION share)
