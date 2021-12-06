# MCU name
MCU = atmega32u4

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
AUDIO_ENABLE        = yes  # Audio output
BACKLIGHT_ENABLE    = no   # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
COMMAND_ENABLE      = no   # Commands for debug and configuration
CONSOLE_ENABLE      = no   # Console for debug
DEBUG_ENABLE        = no   # Enable more debug info
EXTRAKEY_ENABLE     = yes  # Audio control and System control
MOUSEKEY_ENABLE     = no   # Mouse keys
NKRO_ENABLE         = yes  # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE     = yes  # Enable WS2812 RGB underlight.

LAYOUTS = ortho_4x12

DEFAULT_FOLDER = vitamins_included/rev2

LTO_ENABLE = yes
