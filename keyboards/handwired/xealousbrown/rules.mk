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
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = full             # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no                # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes               # Audio control and System control(+450)
CONSOLE_ENABLE = yes                # Console for debug(+400)
COMMAND_ENABLE = yes                 # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no               # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes                   # USB Nkey Rollover
BACKLIGHT_ENABLE = no               # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE = no                    # MIDI controls
UNICODE_ENABLE = no                 # Unicode
BLUETOOTH_ENABLE = no               # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no                   # Audio output on port C6
SPACE_CADET_ENABLE = no             # Unneeded feature.


# special sauce for this keyboard
DEBOUNCE_TYPE = eager_pk            # Debounce using eager_pk.
CUSTOM_MATRIX = lite                # Custom matrix that polls at 7000hz instead of a measly 2000hz.
LINK_TIME_OPTIMIZATION_ENABLE = yes # smaller binary
SRC += matrix.c

# Also remember to open tmk's rules.mk and set compilation optimization to 3
