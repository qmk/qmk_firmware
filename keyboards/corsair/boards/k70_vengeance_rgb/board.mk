# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/k70_vengeance_rgb/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/k70_vengeance_rgb

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
