add_executable(aoc2019-test
    exercise01.cpp
    exercise02.cpp
    exercise03.cpp
    exercise04.cpp
    exercise05.cpp
)

target_link_libraries(aoc2019-test
    PRIVATE
        ${PROJECT_NAME}::aoc-test
)

install(TARGETS aoc2019-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(aoc2019-test aoc2019-test)
