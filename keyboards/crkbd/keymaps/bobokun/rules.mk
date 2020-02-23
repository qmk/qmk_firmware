MOUSEKEY_ENABLE = no
RGB_MATRIX_ENABLE = WS2812
TAP_DANCE_ENABLE= yes
RGBLIGHT_ENABLE = no


# If you want to change the display of OLED, you need to change here
SRC +=  ./keymaps/bobokun/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./keymaps/bobokun/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

EXTRAFLAGS += -flto
