# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay

# If you have Left LEDs (see
# https://geekhack.org/index.php?topic=22780.msg873819#msg873819 for
# details), include the following define:
# OPT_DEFS += -DLEFT_LEDS

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes # Audio control and System control(+450)
CONSOLE_ENABLE   = no  # Console for debug(+400)
COMMAND_ENABLE   = yes # Commands for debug and configuration
CUSTOM_MATRIX    = yes # Custom matrix file for the ErgoDox EZ
NKRO_ENABLE      = yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE   = yes # Unicode
SWAP_HANDS_ENABLE= yes # Allow swapping hands of keyboard
SLEEP_LED_ENABLE = no
API_SYSEX_ENABLE = no
RGBLIGHT_ENABLE = yes
RGBLIGHT_CUSTOM_DRIVER = yes

RGB_MATRIX_ENABLE = no # enable later
DEBOUNCE_TYPE = eager_pr

# project specific files
SRC += matrix.c \
	   led_i2c.c
QUANTUM_LIB_SRC += i2c_master.c

LAYOUTS = ergodox
