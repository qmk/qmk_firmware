# Includes
SRC += features/caps_word.c

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Disable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DYNAMIC_MACRO_ENABLE = yes  # Create macros on the fly
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
INDICATOR_LIGHTS = yes      # Enable indicator lights for caps lock, etc.
# TAP_DANCE_ENABLE = yes      # Send different keycodes if tapped multiple times
# KEY_OVERRIDE_ENABLE = yes   # Override key combos
# COMBO_ENABLE = yes          # Custom key combos

# if firmware size over limit, try this option
# LTO_ENABLE = yes

# DEFAULT_FOLDER = crkbd/rev1

RGBLIGHT_SUPPORTED = yes
RGB_MATRIX_SUPPORTED = yes

# LAYOUTS = split_3x5_3 split_3x6_3
LAYOUTS = split_3x5_3

# Link Time Optimization, saves space, disables some legacy features
# Add the following to config.h to remove disabled features
# #define NO_ACTION_FUNCTION
# #define NO_ACTION_MACRO
EXTRAFLAGS += -flto
