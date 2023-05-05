# BACKLIGHT_ENABLE = yes    # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE= yes            # OLED display
WPM_ENABLE = yes            # Enable WPM counter
TAP_DANCE_ENABLE = yes      # Enable Tap dance
EXTRAFLAGS += -flto         # Enable link time optimization (saves a lot of space)
COMMAND_ENABLE = no         # Enable command
UNICODE_ENABLE = no         # Enable unicode
CONSOLE_ENABLE = no         # Enable console
MAGIC_ENABLE = no           # Enable magic

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/keylogger.c \
        # ./lib/timelogger.c \
        # ./lib/logo_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \