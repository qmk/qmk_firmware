# Build Options
#   change yes to no to disable
#
OLED_ENABLE = yes                   # OLED Enabled

# Cirque touchpad settings
POINTING_DEVICE_ENABLE = yes                    # Pointing Device Enabled
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi    # Pointing Device Driver
DYNAMIC_TAPPING_TERM_ENABLE = yes               # Enable Dynamic Tapping Term to control the Tap term for the Cirque Pad easily

# Custom matrix setup
CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += mcp23018.c matrix.c
QUANTUM_LIB_SRC += i2c_master.c

DEFAULT_FOLDER = mechwild/sugarglider/wide_oled

# Necessary for stenography functionality
KEYBOARD_SHARED_EP = yes    # Needed to free up an endpoint in blackpill
