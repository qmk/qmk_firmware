# MCU name
MCU = STM32F103

# GENERIC STM32F103C8T6 board - mass storage bootloader
MCU_LDSCRIPT = k552_f103
BOARD = k552

BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
BOOTMAGIC_ENABLE = full    # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = yes       # Console for debug
COMMAND_ENABLE = yes       # Commands for debug and configuration
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes          # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
MIDI_ENABLE = no           # MIDI support
UNICODE_ENABLE = no        # Unicode
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no          # Audio output on port C6
LTO_ENABLE = no

## This keyboard have support SWD LED, but i've not figure out for working on STM32F103C8T6.
# Project specific files
# SRC = matrix.c
# SRC += led_matrix.c
# SRC += config_led.c

# Custom RGB matrix handling
# CUSTOM_MATRIX = yes
# RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = custom
