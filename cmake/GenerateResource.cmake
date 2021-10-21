function(generate_resource YEAR EXERCISE)
    set(FILE ${CMAKE_SOURCE_DIR}/res/${YEAR}/${EXERCISE}.dat)
    file(READ ${FILE} CONTENT)
    set(NAME "data_${YEAR}_${EXERCISE}")

    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/include/aoc/res/Resource.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/gen/include/aoc/res/${YEAR}/Data-${EXERCISE}.h
        @ONLY
    )
endfunction()
