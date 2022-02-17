# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = yes          # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SPLIT_KEYBOARD = yes        # Use shared split_common code
SUBPROJECT_rev1 = yes

SRC += matrix.c
DEBOUNCE_TYPE = sym_eager_pk

DEFAULT_FOLDER = handwired/xealous/rev1
