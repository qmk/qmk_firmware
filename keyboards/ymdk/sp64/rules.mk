# MCU name
MCU = atmega32a

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = bootloadHID

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# NKRO_ENABLE = yes		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
#BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
AUDIO_ENABLE = no    # There is no speaker on this PCB
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
CUSTOM_MATRIX = yes

# Needed for underglow
WS2812_DRIVER = i2c

SRC += matrix.c 
QUANTUM_LIB_SRC += i2c_master.c
