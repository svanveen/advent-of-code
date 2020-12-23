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
    exercise10.cpp
    exercise11.cpp
    exercise12.cpp
    exercise13.cpp
    exercise14.cpp
    exercise15.cpp
    exercise16.cpp
    exercise17.cpp
    exercise18.cpp
    exercise19.cpp
    exercise20.cpp
    exercise21.cpp
    exercise22.cpp
    exercise23.cpp
)

target_link_libraries(aoc2020-test
    PRIVATE
        ${PROJECT_NAME}::aoc-test
)

install(TARGETS aoc2020-test
    RUNTIME DESTINATION bin COMPONENT Runtime
)

add_test(aoc2020-test aoc2020-test)
