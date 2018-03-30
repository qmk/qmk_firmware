# Vortex POK3R

SRC = \
	matrix.c \
	backlight.c

LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = HT32F1655_VORTEX

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = VORTEX_DUAL_60

# Vector table for application
# 0x0000-0x2800 is occupied by stock bootloader, which expects the application at 0x2c00
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2c00
