enable_testing()

find_package(GTest REQUIRED)

file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}/res/" "${CMAKE_SOURCE_DIR}/res/*/*.dat")
foreach(RESOURCE IN LISTS RESOURCES)
    get_filename_component(YEAR ${RESOURCE} DIRECTORY)
    get_filename_component(EXERCISE ${RESOURCE} NAME_WE)

    set(TARGET_NAME advent-of-code-${YEAR}-test)
    if (NOT TARGET ${TARGET_NAME})
        add_executable(${TARGET_NAME})
        add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
    endif()

    add_exercise_test(${YEAR} ${EXERCISE}
        ADD_TO_TARGET
            ${TARGET_NAME}
        LINK_LIBRARIES
            GTest::gtest
            GTest::gtest_main
    )
endforeach()
