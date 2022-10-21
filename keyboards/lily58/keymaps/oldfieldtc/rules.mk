# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
EXTRAKEY_ENABLE = yes       # Audio control and System control
WPM_ENABLE = yes	    # Words per minute calculation 

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        ./lib/timelogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \