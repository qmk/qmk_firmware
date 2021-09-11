# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no         # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = no          # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = yes       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no             # USB Nkey Rollover
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_CUSTOM_DRIVER = yes # RGB code is implemented in lfkeyboards, not qmk base
BLUETOOTH_ENABLE = no        # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no            # Audio output on port C6
UNICODE_ENABLE = no          # Unicode
TAP_DANCE_ENABLE = no

ISSI_ENABLE = yes            # If the I2C pullup resistors aren't installed this must be disabled
WATCHDOG_ENABLE = no         # Resets keyboard if matrix_scan() isn't run every 250ms

SRC = TWIlib.c issi.c lighting.c

ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif

LAYOUTS = numpad_6x4
