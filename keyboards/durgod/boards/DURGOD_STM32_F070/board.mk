# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F070RB/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO64_F070RB

# Include mcu configuration
EXTRAINCDIRS = $(BOARD_PATH)/boards/DURGOD_STM32_F070

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
