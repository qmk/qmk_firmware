# project specific files
SRC = \
	backlight.c \
	matrix.c
LAYOUTS += 60_ansi 60_ansi_split_rshift 60_iso

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = HT32
MCU_SERIES = HT32F165x

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = HT32F1655_VORTEX

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = ht32f165x

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = VORTEX_DUAL_60

# Cortex version
MCU = cortex-m3

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

USE_FPU = no

# Vector table for application
# 0x0000-0x2800 is occupied by stock bootloader, which expects the application at 0x2c00
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2c00

# Build Options
# Keys
CUSTOM_MATRIX = yes
NKRO_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = yes
# Boot
BOOTMAGIC_ENABLE = yes  # (Note that BOOTMAGIC on Yoda II is currently non-functional as it lacks an EEPROM driver.)
# Backlight
BACKLIGHT_ENABLE = no
BACKLIGHT_CUSTOM_DRIVER = yes
# Other featues
CONSOLE_ENABLE = yes    # Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes	# Breathing sleep LED during USB suspend
