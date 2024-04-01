# List of all the board related files.
BOARDSRC = $(CHIBIOS_CONTRIB)/os/hal/boards/FS026/board.c

# Required include directories
BOARDINC = $(CHIBIOS_CONTRIB)/os/hal/boards/FS026

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
