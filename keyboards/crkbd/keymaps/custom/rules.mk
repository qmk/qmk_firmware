
# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

# MOUSEKEY_ENABLE = yes
# GBLIGHT_ENABLE = yes# Enable WS2812 RGB underlight.
# BACKLIGHT_ENABLE = yes# Enable keyboard backlight functionality
BACKLIGHT_PIN = D3# Enable keyboard backlight functionality
