# project specific files
SRC =	matrix.c \
	led.c

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
# - For Teensies, FAMILY = KINETIS and SERIES is either
#   KL2x (LC) or K20x (3.0,3.1,3.2).
# - For Infinity KB, SERIES = K20x
MCU_FAMILY = KINETIS
MCU_SERIES = K20x

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

# Startup code to use
#  - it should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
# - STARTUP =
#   - kl2x for Teensy LC
#   - k20x5 for Teensy 3.0 and Infinity KB
#   - k20x7 for Teensy 3.1 and 3.2
MCU_STARTUP = k20x7

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# - BOARD =
#   - PJRC_TEENSY_LC for Teensy LC
#   - PJRC_TEENSY_3 for Teensy 3.0
#   - PJRC_TEENSY_3_1 for Teensy 3.1 or 3.2
#   - MCHCK_K20 for Infinity KB
BOARD = IC_TEENSY_3_1

# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m4

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
# I.e. 6 for Teensy LC; 7 for Teensy 3.x
ARMV = 7

# Vector table for application
# 0x00000000-0x00001000 area is occupied by bootlaoder.*/
# The CORTEX_VTOR... is needed only for MCHCK/Infinity KB
#OPT_DEFS = -DCORTEX_VTOR_INIT=0x00001000
OPT_DEFS =

DFU_ARGS = -d 1c11:b007
DFU_SUFFIX_ARGS = -p b007 -v 1c11

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
#CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = yes # Custom matrix file
BACKLIGHT_ENABLE = yes
VISUALIZER_ENABLE = yes

LED_DRIVER = is31fl3731c
LED_WIDTH = 16
LED_HEIGHT = 5
