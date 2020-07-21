# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/noah_bd/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/noah_bd

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
