# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/STM32_F103XC_STM32DUINO/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/STM32_F103XC_STM32DUINO

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
