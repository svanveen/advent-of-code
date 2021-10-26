enable_testing()

add_executable(advent-of-code-test)
add_test(NAME advent-of-code-test COMMAND advent-of-code)

file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}/res/" "${CMAKE_SOURCE_DIR}/res/*/*.dat")
foreach(RESOURCE IN LISTS RESOURCES)
    get_filename_component(YEAR ${RESOURCE} DIRECTORY)
    get_filename_component(EXERCISE ${RESOURCE} NAME_WE)

    add_exercise_test(${YEAR} ${EXERCISE}
        ADD_TO_TARGET
            advent-of-code-test
        LINK_LIBRARIES
            CONAN_PKG::gtest
    )
endforeach()

install(TARGETS advent-of-code-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)
