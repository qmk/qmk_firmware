# List of all the board related files.
BOARDSRC = $(CHIBIOS_CONTRIB)/os/hal/boards/SN_SN32F240/board.c

# Required include directories
BOARDINC = $(CHIBIOS_CONTRIB)/os/hal/boards/SN_SN32F240

# Optimize for speed
OPT = 2

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)