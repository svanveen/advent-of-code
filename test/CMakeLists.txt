enable_testing()

find_package(GTest REQUIRED)

list_exercises(YEARS EXERCISES)
foreach(YEAR EXERCISE IN ZIP_LISTS YEARS EXERCISES)
    set(TARGET_NAME advent-of-code-${YEAR}-test)
    
    # create a test executable for each year
    if (NOT TARGET ${TARGET_NAME})
        add_executable(${TARGET_NAME})
        target_enable_compiler_warnings(${TARGET_NAME})
        add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
    endif()

    # create an individual test executable for each exercise
    add_exercise_test(${YEAR} ${EXERCISE}
        ADD_TO_TARGET
            ${TARGET_NAME}
        LINK_LIBRARIES
            GTest::gtest
            GTest::gtest_main
    )
endforeach()
