# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_H723ZG/board.c

# Extra files
BOARDSRC += $(BOARD_PATH)/board/extra.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_H723ZG

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
