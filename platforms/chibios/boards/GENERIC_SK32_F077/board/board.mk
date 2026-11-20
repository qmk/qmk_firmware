# List of all the board related files.
# SK32F077: 3Think chip, register-compatible with the STM32F072 except USB.
BOARDSRC = $(CHIBIOS_CONTRIB)/os/hal/boards/GENERIC_SK32_F077/board.c

# Required include directories
BOARDINC = $(CHIBIOS_CONTRIB)/os/hal/boards/GENERIC_SK32_F077

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
