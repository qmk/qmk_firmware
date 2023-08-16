# If you have Left LEDs (see
# https://geekhack.org/index.php?topic=22780.msg873819#msg873819 for
# details), include the following define:
OPT_DEFS += -DLEFT_LEDS

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

CUSTOM_MATRIX = lite        # Custom matrix file for the BAJJAK
UNICODE_ENABLE = yes        # Unicode
SWAP_HANDS_ENABLE = yes     # Allow swapping hands of keyboard

# Disable unsupported hardware
BACKLIGHT_SUPPORTED = no
AUDIO_SUPPORTED = no

DEBOUNCE_TYPE = sym_eager_pr

# project specific files
SRC += matrix.c 
QUANTUM_LIB_SRC += i2c_master.c
