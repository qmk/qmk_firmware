# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/ST_NUCLEO64_F070RB/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/ST_NUCLEO64_F070RB

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
