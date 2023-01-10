# Set the LFK87 hardware version.
#
# A - Green PCB. at90usb1286 Only 3 exist
# B - We don't talk about RevB
# C-D - Black PCB. at90usb646 First public release
#
LFK_REV = C

BOOTLOADER = atmel-dfu
OPT_DEFS += -DLFK_TKL_REV_$(LFK_REV)

# Extra source files for IS3731 lighting
SRC = TWIlib.c issi.c lighting.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no            # Mouse keys
EXTRAKEY_ENABLE = yes           # Audio control and System control
CONSOLE_ENABLE = no             # Console for debug
COMMAND_ENABLE = no             # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes          # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = custom
AUDIO_ENABLE = yes              # Audio output
RGBLIGHT_ENABLE = yes           # Enable RGB underlight
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lefkeyboards, not WS2812
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes			# If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no		# Resets keyboard if matrix_scan isn't run every 250ms
