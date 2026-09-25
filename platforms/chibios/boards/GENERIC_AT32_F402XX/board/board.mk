# List of all the board related files.
BOARDSRC = ${CHIBIOS_CONTRIB}/os/hal/boards/AT_START_F402/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
