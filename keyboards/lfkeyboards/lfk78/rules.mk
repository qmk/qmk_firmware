# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no            # Mouse keys
EXTRAKEY_ENABLE = yes           # Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes               # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = custom
AUDIO_ENABLE = no               # Audio output
RGBLIGHT_ENABLE = yes           # Enable WS2812 RGB underlight.
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lfkeyboards, not qmk base
SLEEP_LED_ENABLE = yes          # Breathing sleep LED during USB suspend

ISSI_ENABLE = yes               # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no            # Resets keyboard if matrix_scan isn't run every 250ms
CAPSLOCK_LED = no              # Toggle back light LED of Caps Lock

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif

ifeq ($(strip $(CAPSLOCK_LED)), yes)
    TMK_COMMON_DEFS += -DCAPSLOCK_LED
endif

DEFAULT_FOLDER = lfkeyboards/lfk78/revj
