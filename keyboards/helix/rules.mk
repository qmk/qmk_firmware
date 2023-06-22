# Build Options
#   change yes to no to disable
#
#   See TOP/docs/config_options.md for more information.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = no    # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
AUDIO_ENABLE = no       # Audio output
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.

DEFAULT_FOLDER = helix/rev2

HELIX_TOP_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
