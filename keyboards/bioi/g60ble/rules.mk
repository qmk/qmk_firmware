# MCU name
MCU = atmega32u4
F_CPU = 8000000

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = qmk-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite    # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes      # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes      # Audio control and System control(+450)
# CONSOLE_ENABLE = yes     # Console for debug(+400)
COMMAND_ENABLE = yes       # Commands for debug and configuration
# SLEEP_LED_ENABLE = yes   # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes          # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes
LTO_ENABLE = yes

LAYOUTS = 60_ansi 60_iso 60_hhkb 60_ansi_split_bs_rshift 60_tsangan_hhkb
