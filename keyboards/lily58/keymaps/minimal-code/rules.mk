BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no          # Audio output
RGBLIGHT_ENABLE = no       # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no     # Enable one-hand typing
OLED_ENABLE= yes           # OLED display

DEBOUNCE_TYPE = asym_eager_defer_pk

SRC +=  ./lib/layer_state_reader.c
