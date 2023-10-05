BOOTMAGIC_ENABLE  = no   # Enable Bootmagic Lite
MOUSEKEY_ENABLE   = no   # Mouse keys
CONSOLE_ENABLE    = no   # Console for debug
COMMAND_ENABLE    = no   # Commands for debug and configuration
NKRO_ENABLE       = no
BACKLIGHT_ENABLE  = no   # Enable keyboard backlight functionality
AUDIO_ENABLE      = no   # Audio output
RGBLIGHT_ENABLE   = no   # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no   # Enable one-hand typing
OLED_ENABLE       = yes  # OLED display
LTO_ENABLE        = yes  # Link time optimisations
EXTRAKEY_ENABLE   = yes  # Audio control and System control

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        ./lib/mode_icon_reader.c \
        ./lib/host_led_state_reader.c \
        ./lib/timelogger.c \
        ./lib/keylogger.c \
        pomodoro.c \
