# add userspace file
SRC += pvinis.c

AUDIO_ENABLE     = no  # piezo speaker sounds
RGBLIGHT_ENABLE  = no  # rgb leds underlight
TAP_DANCE_ENABLE = yes
BACKLIGHT_ENABLE = no  # leds under keycaps
#MOUSEKEY_ENABLE  = no
#SLEEP_LED_ENABLE = no  # no led blinking while sleeping
#NKRO_ENABLE      = yes

# make firmware smaller
LINK_TIME_OPTIMIZATION_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
