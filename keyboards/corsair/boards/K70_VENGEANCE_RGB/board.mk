# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/K70_VENGEANCE_RGB/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/K70_VENGEANCE_RGB

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
