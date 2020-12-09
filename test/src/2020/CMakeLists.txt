add_executable(aoc2020-test
    exercise01.cpp
    exercise02.cpp
    exercise03.cpp
    exercise04.cpp
    exercise05.cpp
    exercise06.cpp
    exercise07.cpp
    exercise08.cpp
    exercise09.cpp
)

target_link_libraries(aoc2020-test
    PRIVATE
        ${PROJECT_NAME}::aoc-test
)

install(TARGETS aoc2020-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(aoc2020-test aoc2020-test)
