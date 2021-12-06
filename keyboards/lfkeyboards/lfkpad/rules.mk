# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no         # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = no          # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no             # USB Nkey Rollover
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
RGBLIGHT_CUSTOM_DRIVER = yes # RGB code is implemented in lfkeyboards, not qmk base
AUDIO_ENABLE = no            # Audio output
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes            # If the I2C pullup resistors aren't installed this must be disabled
WATCHDOG_ENABLE = no         # Resets keyboard if matrix_scan() isn't run every 250ms

SRC = TWIlib.c issi.c lighting.c

LAYOUTS = numpad_6x4
