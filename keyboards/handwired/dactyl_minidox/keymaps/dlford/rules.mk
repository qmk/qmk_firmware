# Includes
SRC += features/caps_word.c

# Build Options
#   change yes to no to disable
#
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
DYNAMIC_MACRO_ENABLE = yes  # Create macros on the fly
INDICATOR_LIGHTS = yes      # Enable indicator lights for caps lock, etc.
# TAP_DANCE_ENABLE = yes      # Send different keycodes if tapped multiple times
# KEY_OVERRIDE_ENABLE = yes   # Override key combos
# COMBO_ENABLE = yes          # Custom key combos

LTO_ENABLE = yes
RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes
