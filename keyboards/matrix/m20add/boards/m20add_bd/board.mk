# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/m20add_bd/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/m20add_bd

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
