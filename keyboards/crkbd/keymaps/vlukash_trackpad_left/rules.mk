# Build Options
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.

BOOTLOADER = atmel-dfu

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \

VPATH += keyboards/crkbd/lib
LIB_SRC += ssd1306.c i2c.c
