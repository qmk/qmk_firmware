# For boards without their own cmake file, simply include a header

# PICO_CMAKE_CONFIG: PICO_BOARD_HEADER_DIRS, Directories to look for <PICO_BOARD>.h in. This is overridable from the user environment, type=list, default="", group=build
if (DEFINED ENV{PICO_BOARD_HEADER_DIRS})
    set(PICO_BOARD_HEADER_DIRS $ENV{PICO_BOARD_HEADER_DIRS})
    message("Using PICO_BOARD_HEADER_DIRS from environment ('${PICO_BOARD_HEADER_DIRS}')")
endif()
set(PICO_BOARD_HEADER_DIRS ${PICO_BOARD_HEADER_DIRS} CACHE STRING "PICO board header directories")

list(APPEND PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/include/boards)
pico_find_in_paths(PICO_BOARD_HEADER_FILE PICO_BOARD_HEADER_DIRS ${PICO_BOARD}.h)

if (EXISTS ${PICO_BOARD_HEADER_FILE})
    message("Using board configuration from ${PICO_BOARD_HEADER_FILE}")
    list(APPEND PICO_CONFIG_HEADER_FILES ${PICO_BOARD_HEADER_FILE})
else()
    set(msg "Unable to find definition of board '${PICO_BOARD}' (specified by PICO_BOARD):\n")
    list(JOIN PICO_BOARD_HEADER_DIRS ", " DIRS)
    string(CONCAT msg ${msg} "   Looked for ${PICO_BOARD}.h in ${DIRS} (additional paths specified by PICO_BOARD_HEADER_DIRS)\n")
    list(JOIN PICO_BOARD_CMAKE_DIRS ", " DIRS)
    string(CONCAT msg ${msg} "   Looked for ${PICO_BOARD}.cmake in ${DIRS} (additional paths specified by PICO_BOARD_CMAKE_DIRS)")
    message(FATAL_ERROR ${msg})
endif()
