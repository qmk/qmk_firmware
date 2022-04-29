# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/adelais_f103/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/adelais_f103

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
