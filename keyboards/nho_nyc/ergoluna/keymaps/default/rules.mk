# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
ENCODER_ENABLE = yes                   # Encoder
MOUSEKEY_ENABLE = yes                  # Mouse keys
OLED_DRIVER_ENABLE= yes                # OLED display
WPM_ENABLE = no                        # Enable WPM Calculator
# FIRMWARE_FORMAT = bin
# After "OLED_DRIVE_ENABLE = yes",if you want to change the display of OLED, you need to change here
# Enable ".lib/wpm_bonggo.c" only when enable "WPM_ENABLE".
SRC +=  ./lib/layer_state_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/keylogger.c \
        ./lib/rgb_state_reader.c \
        ./lib/logo_reader.c \
        #./lib/wpm_bonggo.c \
        #./lib/timelogger.c \
        #./lib/mode_icon_reader.c \

