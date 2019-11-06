KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

SRC += local_drivers/i2c.c
SRC += local_drivers/serial.c
SRC += local_drivers/ssd1306.c
KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers

CUSTOM_MATRIX = yes

SRC += rev2/matrix.c
SRC += rev2/split_util.c
SRC += rev2/split_scomm.c

# Helix Spacific Build Options default values
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (using quantum/rgblight.c)
LED_UNDERGLOW_ENABLE = no   # LED underglow (using quantum/rgblight.c)
LED_ANIMATIONS = yes        # LED animations (quantum/rgblight.c's option)
LED_BACKMTR_ENABLE = no     # LED rgb matrix (using quantum/rgb_matrix.c)
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
