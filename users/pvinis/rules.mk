# add userspace file
SRC += pvinis.c

AUDIO_ENABLE = yes
MOUSEKEY_ENABLE = no
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = no
SLEEP_LED_ENABLE = no # no led blinking while sleeping
# NKRO_ENABLE      = yes

# make firmware smaller
EXTRAFLAGS += -flto
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

BACKLIGHT_ENABLE = no # no key leds installed
