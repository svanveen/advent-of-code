find_package(docopt REQUIRED)
find_package(range-v3 REQUIRED)

add_executable(advent-of-code src/main.cpp)

target_link_libraries(advent-of-code
    PRIVATE
        docopt::docopt
)

file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}/res/" "${CMAKE_SOURCE_DIR}/res/*/*.dat")
foreach(RESOURCE IN LISTS RESOURCES)
    get_filename_component(YEAR ${RESOURCE} DIRECTORY)
    get_filename_component(EXERCISE ${RESOURCE} NAME_WE)

    add_exercise(${YEAR} ${EXERCISE}
        ADD_TO_TARGET
            advent-of-code
        LINK_LIBRARIES
            range-v3::range-v3
    )
endforeach()

install(TARGETS advent-of-code
    RUNTIME DESTINATION bin COMPONENT Runtime
)
