# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/BLACKPILL_STM32_F401/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/BLACKPILL_STM32_F401

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
