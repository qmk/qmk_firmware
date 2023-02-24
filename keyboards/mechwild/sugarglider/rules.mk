# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes              # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes               # Mouse keys
EXTRAKEY_ENABLE = yes               # Audio control and System control
CONSOLE_ENABLE = no                 # Console for debug
COMMAND_ENABLE = no                 # Commands for debug and configuration
NKRO_ENABLE = yes                   # Enable N-Key Rollover
BACKLIGHT_ENABLE = no               # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes               # Enable keyboard RGB underglow
AUDIO_ENABLE = no                   # Audio output
ENCODER_ENABLE = yes                # Encoder Enabled
OLED_ENABLE = yes                   # OLED Enabled
OLED_DRIVER = SSD1306               # OLED Driver
DIP_SWITCH_ENABLE = yes             # Dip Switch Enabled

POINTING_DEVICE_ENABLE = yes                    # Pointing Device Enabled
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi    # Pointing Device Driver

DYNAMIC_TAPPING_TERM_ENABLE = yes               # Enable Dynamic Tapping Term to control the Tap term for the Cirque Pad easily

DEBOUNCE_TYPE = sym_eager_pk

# custom matrix setup
CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += mcp23018.c matrix.c
QUANTUM_LIB_SRC += i2c_master.c

DEFAULT_FOLDER = mechwild/sugarglider/f401

# Necessary for stenography functionality
STENO_ENABLE = yes          # Enable stenography endpoint
NKRO_ENABLE = yes           # Enable N-Key Rollover
KEYBOARD_SHARED_EP = yes    # Needed to free up an endpoint in blackpill