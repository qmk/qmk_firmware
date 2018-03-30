# Vortex POK3R RGB

SRC = \
	matrix.c \
	eeprom.c \
	rgblight.c

LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = HT32F1654_CYKB

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = CYKB167_D_V03

# Vector table for application
# 0x0000-0x2800 is occupied by stock bootloader, which expects the application at 0x2c00
OPT_DEFS = -DCORTEX_VTOR_INIT=0x3400

# Options

# RGB Backlight
RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes
