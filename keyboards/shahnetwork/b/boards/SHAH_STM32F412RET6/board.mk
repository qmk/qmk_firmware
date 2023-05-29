# List of all the board related files.
#BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_F412ZG/board.c
BOARDSRC = $(BOARD_PATH)/boards/SHAH_STM32F412RET6/board.c

# Required include directories
#BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO144_F412ZG
BOARDINC = $(BOARD_PATH)/boards/SHAH_STM32F412RET6

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
