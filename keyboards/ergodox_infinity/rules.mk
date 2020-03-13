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
#   - MK20DX128BLDR4 for Infinity 60% with Kiibohd bootloader
#   - MK20DX256BLDR8 for Infinity ErgoDox with Kiibohd bootloader
MCU_LDSCRIPT = MK20DX256BLDR8

# Vector table for application
# 0x00000000-0x00001000 area is occupied by bootlaoder.*/
# The CORTEX_VTOR... is needed only for MCHCK/Infinity KB
OPT_DEFS += -DCORTEX_VTOR_INIT=0x00002000

BOOTLOADER = dfu

# Build Options
#   comment out to disable the options.
#

DFU_ARGS = -d 1c11:b007
DFU_SUFFIX_ARGS = -p b007 -v 1c11

BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
CONSOLE_ENABLE   = no  # Console for debug
COMMAND_ENABLE   = yes # Commands for debug and configuration
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
SLEEP_LED_ENABLE = yes # Breathing sleep LED during USB suspend
NKRO_ENABLE      = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE   = yes # Unicode
SWAP_HANDS_ENABLE= yes # Allow swapping hands of keyboard

CUSTOM_MATRIX = yes # Custom matrix file
SERIAL_LINK_ENABLE = yes
VISUALIZER_ENABLE = yes
LCD_ENABLE = yes
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = custom
LCD_BACKLIGHT_ENABLE = yes
MIDI_ENABLE = no
RGBLIGHT_ENABLE = no

LCD_DRIVER = st7565
LCD_WIDTH = 128
LCD_HEIGHT = 32

LED_DRIVER = is31fl3731c
LED_WIDTH = 7
LED_HEIGHT = 7

# project specific files
SRC = matrix.c \
      led.c

LAYOUTS = ergodox
