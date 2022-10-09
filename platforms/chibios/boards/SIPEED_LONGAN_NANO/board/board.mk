# List of all the board related files.
BOARDSRC = ${CHIBIOS_CONTRIB}/os/hal/boards/SIPEED_LONGAN_NANO/board.c

# Required include directories
BOARDINC = ${CHIBIOS_CONTRIB}/os/hal/boards/SIPEED_LONGAN_NANO

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
