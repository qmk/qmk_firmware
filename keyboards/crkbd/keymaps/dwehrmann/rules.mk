TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
MOUSEKEY_ENABLE = yes
LOCAL_GLCDFONT = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/glcdfont.c \
        ./lib/rgb_state_reader.c \
        ./lib/keylogger.c \
        ./lib/mode_icon_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/timelogger.c \
