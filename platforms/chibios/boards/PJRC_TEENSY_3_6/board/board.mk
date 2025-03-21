include $(CHIBIOS_CONTRIB)/os/hal/boards/PJRC_TEENSY_3_6/board.mk

# List of all the board related files.
BOARDSRC += $(BOARD_PATH)/board/extra.c

# Required include directories
BOARDINC += $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
