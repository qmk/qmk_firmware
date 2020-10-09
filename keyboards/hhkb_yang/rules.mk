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
BOOTLOADER = lufa-ms

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = yes   # Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Custom matrix file for the HHKB
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
# NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = yes       # MIDI controls
# UNICODE_ENABLE = yes    # Unicode
# BLUETOOTH_ENABLE = yes  # Enable Bluetooth with the Adafruit EZ-Key HID
# BLUETOOTH = AdafruitBLE_UART

# project specific files
SRC = matrix.c

# debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
# debug-on: all

# debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
# debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
# debug-off: all

LAYOUTS = 60_hhkb

F_CPU = 8000000
PROGRAM_CMD = sudo umount /dev/sda \
	&& sudo dd if=$(BUILD_DIR)/$(TARGET).bin of=/dev/sda seek=4 \
	&& sudo eject /dev/sda
