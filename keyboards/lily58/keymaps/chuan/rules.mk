EXTRAKEY_ENABLE = yes
NKRO_ENABLE = yes
ENCODER_ENABLE = yes
# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/mode_icon_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/timelogger.c \
        ./lib/keylogger.c \
