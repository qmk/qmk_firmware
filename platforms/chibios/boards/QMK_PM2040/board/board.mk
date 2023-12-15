# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/RP_PICO_RP2040/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/RP_PICO_RP2040

# Shared variables
ALLCSRC += $(BOARDSRC) 
ALLINC  += $(BOARDINC)
