# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/board/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
