# MCU name
MCU = atmega32u2

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no		# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes  # In-switch LEDs
AUDIO_ENABLE = no      # There is no available timer or pin for audio on the NovelPad
RGBLIGHT_ENABLE = yes  # RGB LEDs for underglow, installed and enabled by default for the NovelPad

LAYOUTS = ortho_5x4
