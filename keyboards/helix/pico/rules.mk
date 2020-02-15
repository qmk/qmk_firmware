KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

SRC += local_drivers/i2c.c
SRC += local_drivers/serial.c
SRC += local_drivers/ssd1306.c
KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers

# A workaround until #7089 is merged.
#   serial.c must not be compiled with the -lto option.
#   The current LIB_SRC has a side effect with the -fno-lto option, so use it.
LIB_SRC += local_drivers/serial.c

CUSTOM_MATRIX = yes

SRC += pico/matrix.c
SRC += pico/split_util.c

# Helix Spacific Build Options default values
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
