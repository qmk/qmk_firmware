MOUSEKEY_ENABLE   = yes
EXTRAKEY_ENABLE   = yes

BOOTMAGIC_ENABLE  = no
CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no
NKRO_ENABLE       = no
BACKLIGHT_ENABLE  = no
MIDI_ENABLE       = no
AUDIO_ENABLE      = no
UNICODE_ENABLE    = no
BLUETOOTH_ENABLE  = no
RGBLIGHT_ENABLE   = no
SWAP_HANDS_ENABLE = no
OLED_ENABLE       = no
SLEEP_LED_ENABLE  = no

SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
