# project specific files
SRC =	backlight.c \
	matrix.c
LAYOUTS += 60_ansi 60_ansi_split_bs_rshift 60_iso

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
MCU  = cortex-m3

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

USE_FPU = no

# Vector table for application
# 0x00000000-0x00003400 area is occupied by bootloader.*/
# The CORTEX_VTOR... is needed only for bootloader
OPT_DEFS = -DCORTEX_VTOR_INIT=0x00003400
#OPT_DEFS =

# Options to pass to dfu-util when flashing
#DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = yes
BACKLIGHT_CUSTOM_DRIVER = yes
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
## (Note that BOOTMAGIC on Yoda II is currently non-functional as it lacks an EEPROM driver.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes	# Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	# USB Nkey Rollover
CUSTOM_MATRIX = yes # Custom matrix file
