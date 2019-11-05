KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

ifneq ($(strip $(NO_LTO_SRC_TEST)),)
  SRC += local_drivers/i2c.c
  ifeq ($(strip $(NO_LTO_SRC_TEST)),no-lto)
    SRC += local_drivers/serial.c/NO-LTO
  else
    SRC += local_drivers/serial.c
  endif
  SRC += local_drivers/ssd1306.c
  $(info SRC=$(SRC))
else
  ifeq ($(strip $(NO_LTO_LIB_TEST)),no-lto)
    LIB_SRC += local_drivers/serial.c/NO-LTO
  else
    LIB_SRC += local_drivers/serial.c
  endif
  LIB_SRC += local_drivers/ssd1306.c
  LIB_SRC += local_drivers/i2c.c
  $(info LIB_SRC=$(LIB_SRC))
endif

KEYBOARD_PATHS += $(HELIX_TOP_DIR)/local_drivers

CUSTOM_MATRIX = yes

SRC += rev2/matrix.c
SRC += rev2/split_util.c
SRC += rev2/split_scomm.c

# Helix Spacific Build Options default values
HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
