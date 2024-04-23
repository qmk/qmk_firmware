# MCU name
MCU = STM32F411

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = noah_boot

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = ST_NUCLEO64_F411RE

# Bootloader selection
BOOTLOADER = custom

WS2812_DRIVER_REQUIRED = yes

CUSTOM_MATRIX = yes
# project specific files
SRC += matrix.c
