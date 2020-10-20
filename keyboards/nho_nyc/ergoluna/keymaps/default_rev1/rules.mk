# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

MOUSEKEY_ENABLE = yes                  # Mouse keys
RGBLIGHT_ENABLE = yes                  # Enable WS2812 RGB underlight.
OLED_DRIVER_ENABLE= yes                # OLED display
WPM_ENABLE = no                        # Enable WPM Calculator

# After "OLED_DRIVE_ENABLE = yes",If you want to change the display of OLED, you need to change here
# Enable ".lib/wpm_bonggo.c" only when enable "WPM_ENABLE".
SRC +=  ./rev1/lib/layer_state_reader.c \
        ./rev1/lib/host_led_state_reader.c \
        ./rev1/lib/keylogger.c \
        ./rev1/lib/rgb_state_reader.c \
        ./rev1/lib/logo_reader.c \
        #./rev1/lib/wpm_bonggo.c \
        #./rev1/lib/timelogger.c \
        #./rev1/lib/mode_icon_reader.c \

