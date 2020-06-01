BOOTLOADER = atmel-dfu  # Elite-C

MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c
