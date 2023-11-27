# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no         # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = no          # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
AUDIO_ENABLE = no            # Audio output
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes            # If the I2C pullup resistors aren't installed this must be disabled
WATCHDOG_ENABLE = no         # Resets keyboard if matrix_scan() isn't run every 250ms

SRC = TWIlib.c issi.c lighting.c
