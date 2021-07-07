RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
AUTO_SHIFT_ENABLE = yes
OLED_DRIVER_ENABLE= yes     # OLED display

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
