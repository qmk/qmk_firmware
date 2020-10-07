# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

MOUSEKEY_ENABLE = no                  # Mouse keys
RGBLIGHT_ENABLE = no                   # Enable WS2812 RGB underlight. 
RGB_MATRIX_ENABLE = no             # Change into "WS2812" to enable RGB Matrix; "no" to off. Enable only when compiled with  "make nho_nyc/ergoluna/rev2:default"
OLED_DRIVER_ENABLE= yes                # OLED display
WPM_ENABLE = yes                       # Enable WPM Calculator

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/layer_state_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/keylogger.c \
		./lib/rgb_state_reader.c \
		./lib/logo_reader.c \
		./lib/wpm_bonggo.c \
        #./lib/timelogger.c \
        #./lib/mode_icon_reader.c \



