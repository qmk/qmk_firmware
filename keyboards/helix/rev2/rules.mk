KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

# Helix Spacific Build Options default values
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = yes           # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)

# If OLED_ENABLE is 'yes'
#   If OLED_SELECT is 'core', use QMK standard oled_dirver.c.
#   If OLED_SELECT is other than 'core', use helix/local_drivers/ssd1306.c.
OLED_SELECT = local
