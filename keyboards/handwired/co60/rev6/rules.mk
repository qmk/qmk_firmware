# project specific files

## chip/board settings
# - the next two should match the directories in
#   <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F3xx

# Linker script to use
# - it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#   or <this_dir>/ld/
MCU_LDSCRIPT = STM32F303xC

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f3xx

# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = GENERIC_STM32_F303XC

# Cortex version
MCU  = cortex-m4

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

USE_FPU = yes

# Vector table for application
# 0x00000000-0x00001000 area is occupied by bootlaoder.*/
# The CORTEX_VTOR... is needed only for MCHCK/Infinity KB
# OPT_DEFS = -DCORTEX_VTOR_INIT=0x08005000

# Options to pass to dfu-util when flashing
DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave
DFU_SUFFIX_ARGS = -v 0483 -p df11

# Code for backlight breathing:
SRC += led.c

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = yes
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes   # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes   # Audio control and System control(+450)
CONSOLE_ENABLE = no    # Console for debug(+400)
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no    # Enable keyboard underlight functionality
MIDI_ENABLE = no        # MIDI controls
UNICODE_ENABLE = no     # Unicode
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
LEADER_ENABLE = yes

LAYOUTS += 60_ansi 60_ansi_split_bs_rshift 60_iso 60_hhkb
