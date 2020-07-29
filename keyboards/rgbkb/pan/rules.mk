# Processor choice= comment out either line 2 or 3.
# ATmega32A = yes
# ProtonC = yes



# MCU name
# MCU = atmega32a

# Processor frequency
# F_CPU = 16000000

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
# BOOTLOADER = USBasp

# disable debug code
OPT_DEFS = -DDEBUG_LEVEL=0

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE      = lite   # Virtual DIP switch configuration
MOUSEKEY_ENABLE       = no     # Mouse keys
EXTRAKEY_ENABLE       = yes    # Audio control and System control
CONSOLE_ENABLE        = no     # Console for debug
COMMAND_ENABLE        = no     # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE      = no     # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE           = no     # USB Nkey Rollover
MIDI_ENABLE           = no     # MIDI support
UNICODE_ENABLE        = no     # Unicode
BLUETOOTH_ENABLE      = no     # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE          = no     # Audio output on port C6
FAUXCLICKY_ENABLE     = no     # Use buzzer to emulate clicky switches
HD44780_ENABLE        = no 	   # Enable support for HD44780 based LCDs
RGB_MATRIX_ENABLE     = WS2812 # RGB matrix animations
WS2812_DRIVER         = bitbang
ENCODER_ENABLE        = yes
OLED_DRIVER_ENABLE    = yes

# RGB layout selection
RGB_ENCODERS          = yes    # For RGB encoders, solder on both WS2811 chips
STAGGERED_LAYOUT      = no     # If you soldered R1-A12 and R4-A12, enable this.

# DEFAULT_FOLDER = rgbkb/pan/rev1_atmega