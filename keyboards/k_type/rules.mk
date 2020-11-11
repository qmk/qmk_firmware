# MCU name
MCU = MK20DX256

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
# - NOTE: a custom ld script is needed for EEPROM on Teensy LC
# - LDSCRIPT =
#   - MKL26Z64 for Teensy LC
#   - MK20DX128 for Teensy 3.0
#   - MK20DX256 for Teensy 3.1 and 3.2
#   - MK20DX128BLDR4 for Infinity with Kiibohd bootloader
#   - MK20DX256BLDR8 for Infinity ErgoDox with Kiibohd bootloader
MCU_LDSCRIPT = MK20DX256BLDR8

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# This board was copied from PJRC_TEENSY_3_1. The only difference should be a
# hack to ensure the watchdog has started before trying to disable it.
BOARD = IC_TEENSY_3_1

DFU_ARGS = -d 1c11:b007
DFU_SUFFIX_ARGS = -p b007 -v 1c11

BOOTLOADER = dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = yes # Custom matrix file
DEBUG_ENABLE = yes

# project specific files
SRC = matrix.c

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
