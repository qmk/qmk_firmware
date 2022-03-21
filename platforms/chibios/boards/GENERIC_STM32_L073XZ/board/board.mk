# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_L073RZ/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_L073RZ

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
