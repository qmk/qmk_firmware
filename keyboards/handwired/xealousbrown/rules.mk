# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
SPACE_CADET_ENABLE = no     # Unneeded feature.

LAYOUTS = 60_ansi

# special sauce for this keyboard
DEBOUNCE_TYPE = sym_eager_pk    # Debounce using eager_pk.
CUSTOM_MATRIX = lite        # Custom matrix that polls at 7000hz instead of a measly 2000hz.
LTO_ENABLE = yes            # smaller binary
SRC += matrix.c

# Also remember to open tmk's rules.mk and set compilation optimization to 3
