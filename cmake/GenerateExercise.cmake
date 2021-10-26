include(${CMAKE_CURRENT_LIST_DIR}/GenerateResource.cmake)

function(get_target_name VAR NAME YEAR EXERCISE)
    cmake_parse_arguments(NAME "" "PREFIX;SUFFIX" "" ${ARGN})
    if (EXERCISE LESS 10)
        set(EXERCISE "0${EXERCISE}")
    endif()
    set(NAME "${NAME}-${YEAR}-${EXERCISE}")
    if (NAME_PREFIX)
        set(NAME "${NAME_PREFIX}-${NAME}")
    endif()
    if (NAME_SUFFIX)
        set(NAME "${NAME}-${NAME_SUFFIX}")
    endif()
    set(${VAR} ${NAME} PARENT_SCOPE)
endfunction()

function(_add_exercise_impl NAME YEAR EXERCISE)
    cmake_parse_arguments(ARG "" "" "LIBRARIES;SOURCES" ${ARGN})

    get_target_name(TARGET_NAME ${NAME} ${YEAR} ${EXERCISE})
    get_target_name(OBJECT_TARGET_NAME ${NAME} ${YEAR} ${EXERCISE} PREFIX obj)

    if (EXERCISE LESS 10)
        set(EXERCISE "0${EXERCISE}")
    endif()

    add_library(${OBJECT_TARGET_NAME} OBJECT
        src/${YEAR}/exercise${EXERCISE}.cpp
    )

    foreach(LIBRARY IN LISTS ARG_LIBRARIES)
        target_link_libraries(${OBJECT_TARGET_NAME} PUBLIC ${PROJECT_NAME}::${LIBRARY})
    endforeach()

    add_executable(${TARGET_NAME}
        EXCLUDE_FROM_ALL
        $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
    )

    foreach(SOURCE IN LISTS ARG_SOURCES)
        target_sources(${TARGET_NAME} PUBLIC ${SOURCE})
    endforeach()

    target_link_libraries(${TARGET_NAME} PRIVATE ${OBJECT_TARGET_NAME})
endfunction()

function(add_exercise YEAR EXERCISE OBJECT_TARGET)
    generate_resource(${YEAR} ${EXERCISE})

    set(TARGET_MAIN ${CMAKE_CURRENT_BINARY_DIR}/gen/src/${YEAR}/${EXERCISE}/main.cpp)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exercise-main.cpp.in
        ${TARGET_MAIN}
        @ONLY
    )

    _add_exercise_impl(exercise ${YEAR} ${EXERCISE}
        LIBRARIES aoc
        SOURCES ${TARGET_MAIN}
    )

    get_target_name(OBJECT_TARGET_NAME exercise ${YEAR} ${EXERCISE} PREFIX obj)
    set(${OBJECT_TARGET} ${OBJECT_TARGET_NAME} PARENT_SCOPE)
endfunction()

function(add_exercise_test YEAR EXERCISE)
    get_target_name(OBJECT_TARGET_NAME exercise ${YEAR} ${EXERCISE} PREFIX obj)
    _add_exercise_impl(test ${YEAR} ${EXERCISE}
        LIBRARIES aoc-test
        SOURCES $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
    )

    get_target_name(TEST_TARGET_NAME test ${YEAR} ${EXERCISE})
    add_test(NAME ${TEST_TARGET_NAME} COMMAND ${TEST_TARGET_NAME})
endfunction()
