include(${CMAKE_CURRENT_LIST_DIR}/GenerateResource.cmake)

function(get_target_name VAR NAME YEAR EXERCISE)
    cmake_parse_arguments(NAME "" "PREFIX;SUFFIX" "" ${ARGN})
    set(NAME "${NAME}-${YEAR}-${EXERCISE}")
    if (NAME_PREFIX)
        set(NAME "${NAME_PREFIX}-${NAME}")
    endif()
    if (NAME_SUFFIX)
        set(NAME "${NAME}-${NAME_SUFFIX}")
    endif()
    set(${VAR} ${NAME} PARENT_SCOPE)
endfunction()

function(add_exercise YEAR EXERCISE OBJECT_TARGET)
    generate_resource(${YEAR} ${EXERCISE})

    set(TARGET_MAIN ${CMAKE_CURRENT_BINARY_DIR}/gen/src/${YEAR}/${EXERCISE}/main.cpp)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exercise-main.cpp.in
        ${TARGET_MAIN}
        @ONLY
    )

    if (EXERCISE LESS 10)
        set(EXERCISE "0${EXERCISE}")
    endif()

    get_target_name(TARGET_NAME exercise ${YEAR} ${EXERCISE})
    get_target_name(OBJECT_TARGET_NAME exercise ${YEAR} ${EXERCISE} PREFIX obj)
    set(${OBJECT_TARGET} ${OBJECT_TARGET_NAME} PARENT_SCOPE)

    add_library(${OBJECT_TARGET_NAME} OBJECT
        src/${YEAR}/exercise${EXERCISE}.cpp
    )

    target_link_libraries(${OBJECT_TARGET_NAME} PUBLIC ${PROJECT_NAME}::aoc)

    add_executable(${TARGET_NAME}
        ${TARGET_MAIN}
        $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
    )

    target_link_libraries(${TARGET_NAME} PRIVATE ${OBJECT_TARGET_NAME})
endfunction()

function(add_exercise_test YEAR EXERCISE)
    if (EXERCISE LESS 10)
        set(EXERCISE "0${EXERCISE}")
    endif()

    get_target_name(TEST_TARGET_NAME test ${YEAR} ${EXERCISE})
    get_target_name(TEST_OBJECT_TARGET_NAME test ${YEAR} ${EXERCISE} PREFIX obj)
    get_target_name(OBJECT_TARGET_NAME exercise ${YEAR} ${EXERCISE} PREFIX obj)

    add_library(${TEST_OBJECT_TARGET_NAME} OBJECT
        src/${YEAR}/exercise${EXERCISE}.cpp
    )

    target_link_libraries(${TEST_OBJECT_TARGET_NAME} PUBLIC ${PROJECT_NAME}::aoc-test)

    add_executable(${TEST_TARGET_NAME}
        $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
        $<TARGET_OBJECTS:${TEST_OBJECT_TARGET_NAME}>
    )

    target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${TEST_OBJECT_TARGET_NAME})

    add_test(NAME ${TEST_TARGET_NAME} COMMAND ${TEST_TARGET_NAME})
endfunction()
