# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F446RE/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F446RE

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
