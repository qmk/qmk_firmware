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
AUDIO_ENABLE = no               # Audio output
RGBLIGHT_ENABLE = yes           # Enable WS2812 RGB underlight.
RGBLIGHT_CUSTOM_DRIVER = yes    # RGB code is implemented in lfkeyboards, not qmk base
SLEEP_LED_ENABLE = yes

ISSI_ENABLE = yes               # If the I2C pullup resistors aren't install this must be disabled
WATCHDOG_ENABLE = no            # Resets keyboard if matrix_scan isn't run every 250ms
CAPSLOCK_LED = no              # Toggle back light LED of Caps Lock

DEFAULT_FOLDER = lfkeyboards/lfk78/revj
