# PICO_CMAKE_CONFIG: PICO_BOARD, The board name being built for. This is overridable from the user environment, type=string, default=pico, group=build
if (DEFINED ENV{PICO_BOARD})
    set(PICO_BOARD $ENV{PICO_BOARD})
    message("Using PICO_BOARD from environment ('${PICO_BOARD}')")
else()
    if (NOT PICO_BOARD)
        set(PICO_BOARD "pico")
        pico_message("Defaulting PICO target board to ${PICO_BOARD} since not specified.")
    else()
        message("PICO target board is ${PICO_BOARD}.")
    endif()
endif()
set(PICO_BOARD ${PICO_BOARD} CACHE STRING "PICO target board (e.g. pico)")

# PICO_CMAKE_CONFIG: PICO_BOARD_CMAKE_DIRS, Directories to look for <PICO_BOARD>.cmake in. This is overridable from the user environment, type=list, default="", group=build
if (DEFINED ENV{PICO_BOARD_CMAKE_DIRS})
    set(PICO_BOARD_CMAKE_DIRS $ENV{PICO_BOARD_CMAKE_DIRS})
    message("Using PICO_BOARD_CMAKE_DIRS from environment ('${PICO_BOARD_CMAKE_DIRS}')")
endif()

list(APPEND PICO_BOARD_CMAKE_DIRS ${CMAKE_CURRENT_LIST_DIR}/boards)

pico_find_in_paths(PICO_BOARD_CMAKE_FILE PICO_BOARD_CMAKE_DIRS ${PICO_BOARD}.cmake)
if (EXISTS "${PICO_BOARD_CMAKE_FILE}")
    message("Using CMake board configuration from ${PICO_BOARD_CMAKE_FILE}")
    include(${PICO_BOARD_CMAKE_FILE} board_config)
else()
    include(boards/generic_board.cmake)
endif()

list(APPEND PICO_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/boards/include) # so boards/foo.h can be explicitly included
