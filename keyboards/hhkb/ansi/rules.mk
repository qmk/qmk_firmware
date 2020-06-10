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
BOOTLOADER = atmel-dfu

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


# HHKB_RN42_ENABLE = yes  # Enable support for hasu's BT alt controller -- code borrowed from tmk source tree.

# Either uncomment the HHKB_RN42_ENABLE line above, or run make enabling the
# feature. Be sure to clean any existing build before trying to enable rn42
# support. For example:
#
# make hhkb-keymap-clean
# make hhkb-keymap-dfu HHKB_RN42_ENABLE=yes

# project specific files
SRC = matrix.c

ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)

OPT_DEFS += -DHHKB_RN42_ENABLE

# Support for the RN42 Bluetooth module. This is the BT module in Hasu's BT
# HHKB Alt controller.
RN42_DIR = ../rn42

SRC +=  serial_uart.c \
	../rn42/suart.S \
	../rn42/rn42.c \
	../rn42/rn42_task.c \
	../rn42/battery.c \
	../rn42/main.c

VPATH += $(RN42_DIR)

endif


# debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
# debug-on: all

# debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
# debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
# debug-off: all

LAYOUTS = 60_hhkb
