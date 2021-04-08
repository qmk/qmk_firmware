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
BOOTLOADER = qmk-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE  = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE   = no  # Audio control and System control(+450)
CONSOLE_ENABLE    = yes # Console for debug(+400)
COMMAND_ENABLE    = no  # Commands for debug and configuration
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE       = no  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE  = no  # Custom backlighting code is used, so this should not be enabled
AUDIO_ENABLE      = no  # This can be enabled if a speaker is connected to the expansion port. Not compatible with RGBLIGHT below
RGBLIGHT_ENABLE   = no  # This can be enabled if a ws2812 strip is connected to the expansion port.

LAYOUTS = ortho_5x12
