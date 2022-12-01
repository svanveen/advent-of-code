include(${CMAKE_CURRENT_LIST_DIR}/GenerateResource.cmake)

macro(list_exercises OUT_YEARS OUT_EXERCISES)
    file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}/res/" "${CMAKE_SOURCE_DIR}/res/*/*.dat")
    foreach(RESOURCE IN LISTS RESOURCES)
        get_filename_component(YEAR ${RESOURCE} DIRECTORY)
        get_filename_component(EXERCISE ${RESOURCE} NAME_WE)
        list(APPEND ${OUT_YEARS} ${YEAR})
        list(APPEND ${OUT_EXERCISES} ${EXERCISE})
    endforeach()
endmacro()

macro(exercise_number OUT EXERCISE)
    string(REGEX REPLACE "0([1-9])" "\\1" ${OUT} ${EXERCISE})
endmacro()

function(generate_source_file YEAR EXERCISE SOURCE TARGET)
    exercise_number(EXERCISE_NUMBER ${EXERCISE})
    configure_file(${SOURCE} ${TARGET} @ONLY)
endfunction()

function(get_target_name OUT NAME YEAR EXERCISE)
    cmake_parse_arguments(NAME "" "PREFIX;SUFFIX" "" ${ARGN})
    set(NAME "${NAME}-${YEAR}-${EXERCISE}")
    if (NAME_PREFIX)
        set(NAME "${NAME_PREFIX}-${NAME}")
    endif()
    if (NAME_SUFFIX)
        set(NAME "${NAME}-${NAME_SUFFIX}")
    endif()
    set(${OUT} ${NAME} PARENT_SCOPE)
endfunction()

function(add_exercise_impl NAME YEAR EXERCISE)
    cmake_parse_arguments(ARG "IS_TEST" "ADD_TO_TARGET" "LINK_LIBRARIES;EXECUTABLE_SOURCES;OBJECT_SOURCES" ${ARGN})

    get_target_name(TARGET_NAME ${NAME} ${YEAR} ${EXERCISE})
    get_target_name(OBJECT_TARGET_NAME ${NAME} ${YEAR} ${EXERCISE} PREFIX obj)

    set(SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/${YEAR}/Exercise${EXERCISE}.cpp)
    if (NOT EXISTS ${SOURCE_FILE})
        generate_source_file(${YEAR} ${EXERCISE}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Exercise.cpp.in
            ${SOURCE_FILE}
        )
    endif()

    add_library(${OBJECT_TARGET_NAME} OBJECT
        ${SOURCE_FILE}
    )

    target_include_directories(${OBJECT_TARGET_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_BINARY_DIR}/gen/include
    )

    target_compile_features(${OBJECT_TARGET_NAME} PUBLIC cxx_std_17)

    target_sources(${OBJECT_TARGET_NAME} PUBLIC ${ARG_OBJECT_SOURCES})

    target_link_libraries(${OBJECT_TARGET_NAME} PUBLIC ${ARG_LINK_LIBRARIES})

    target_sources(${ARG_ADD_TO_TARGET}
        PRIVATE
            $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
    )
    target_link_libraries(${ARG_ADD_TO_TARGET}
        PUBLIC
            ${OBJECT_TARGET_NAME}
    )

    add_executable(${TARGET_NAME}
        EXCLUDE_FROM_ALL
        $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
    )

    target_sources(${TARGET_NAME} PUBLIC ${ARG_EXECUTABLE_SOURCES})

    target_link_libraries(${TARGET_NAME} PRIVATE ${OBJECT_TARGET_NAME})

    if (ARG_IS_TEST)
        add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
    endif()
endfunction()

function(add_exercise YEAR EXERCISE)
    generate_resource(${YEAR} ${EXERCISE})

    set(TARGET_MAIN ${CMAKE_CURRENT_BINARY_DIR}/gen/src/${YEAR}/${EXERCISE}/main.cpp)
    generate_source_file(${YEAR} ${EXERCISE}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exercise-main.cpp.in
        ${TARGET_MAIN}
    )

    add_exercise_impl(exercise ${YEAR} ${EXERCISE} ${ARGN}
        EXECUTABLE_SOURCES
            ${TARGET_MAIN}
    )
endfunction()

function(add_exercise_test YEAR EXERCISE)
    get_target_name(OBJECT_TARGET_NAME exercise ${YEAR} ${EXERCISE} PREFIX obj)
    add_exercise_impl(test ${YEAR} ${EXERCISE} ${ARGN}
        LINK_LIBRARIES
            ${OBJECT_TARGET_NAME}
        OBJECT_SOURCES
            $<TARGET_OBJECTS:${OBJECT_TARGET_NAME}>
        IS_TEST
    )
endfunction()
