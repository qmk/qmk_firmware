CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
MOUSEKEY_ENABLE = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = WS2812
OLED_DRIVER_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  ./keyboards/crkbd/keymaps/kidbrazil/logo_reader.c \
        #./lib/rgb_state_reader.c \
        #./lib/logo_reader.c \
        #./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \
