add_library(aoc)
add_library(${PROJECT_NAME}::aoc ALIAS aoc)

target_sources(aoc
    PRIVATE
        src/2020/exercise01.cpp
        src/2020/exercise02.cpp
        src/2020/exercise03.cpp
        src/2020/exercise04.cpp
        src/2020/exercise05.cpp
        src/2020/exercise06.cpp
        src/2020/exercise07.cpp
        src/2020/exercise08.cpp
        src/2020/exercise09.cpp
        src/2020/exercise10.cpp
        src/2020/exercise11.cpp
        src/2020/exercise12.cpp
        src/2020/exercise13.cpp
        src/2020/exercise14.cpp
        src/2020/exercise15.cpp
        src/2020/exercise16.cpp
        src/2020/exercise17.cpp
        src/2020/exercise18.cpp
        src/2020/exercise19.cpp
        src/2020/exercise20.cpp
        src/2020/exercise21.cpp
        src/2020/exercise22.cpp
        src/2020/exercise23.cpp
        src/2020/exercise24.cpp
        src/2020/exercise25.cpp
)

target_include_directories(aoc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/gen/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(aoc
    PUBLIC
        CONAN_PKG::range-v3
)

target_compile_features(aoc
    PUBLIC
        cxx_std_17
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)

install(TARGETS aoc
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
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/gen/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
