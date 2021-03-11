# MCU name
MCU = STM32F303
CTPC = yes
BOARD = QMK_PROTON_C
DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
#Outputs matrix scan rate in QMK Toolbox


# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = lite       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = off        # Commands for debug and configuration
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID

SERIAL_DRIVER = usart
OLED_DRIVER_ENABLE = yes

RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = pwm


# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = mirror    # for when Split Mirroring drops, it will maintain mirroring functionality

# if firmware size over limit, try this option
# CFLAGS += -flto

# The following is for the old way of doing oleds
SRC += ./lib/glcdfont.c \
    #    ./lib/rgb_state_reader.c \
    #    ./lib/keylogger.c \
    #    ./lib/mode_icon_reader.c \
    #    ./lib/host_led_state_reader.c \
    #    ./lib/timelogger.c \
    #    ./lib/logo_reader.c

DEFAULT_FOLDER = bakekujira
LAYOUTS = ansi_split
