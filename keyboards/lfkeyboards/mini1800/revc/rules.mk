# MCU name
MCU = at90usb646

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
AUDIO_ENABLE = yes          # Audio output

# RGB code is implemented in lfkeyboards, not WS2812
RGBLIGHT_CUSTOM_DRIVER = yes
BACKLIGHT_DRIVER = custom
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes           # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = yes       # Resets keyboard if matrix_scan isn't run every 250ms

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c
