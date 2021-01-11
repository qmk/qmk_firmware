MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   atmega32a    bootloadHID
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no        # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no             # USB Nkey Rollover
BACKLIGHT_ENABLE = yes       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
MIDI_ENABLE = no             # MIDI support
UNICODE_ENABLE = no          # Unicode
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no            # Audio output on port C6
FAUXCLICKY_ENABLE = no       # Use buzzer to emulate clicky switches
HD44780_ENABLE = no          # Enable support for HD44780 based LCDs
EXTRAFLAGS += -flto

LAYOUTS = numpad_5x4