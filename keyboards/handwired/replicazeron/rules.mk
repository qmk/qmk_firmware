AUDIO_ENABLE = no
BACKLIGHT_ENABLE = no
COMMAND_ENABLE = no
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
OLED_ENABLE = yes
TAP_DANCE_ENABLE = no

LEDS_ENABLE = yes
THUMBSTICK_ENABLE = yes

SRC += state.c

VPATH += keyboards/handwired/replicazeron/common

# redirect compilation against "handwired/replicazeron" to the stm32 variant
DEFAULT_FOLDER = handwired/replicazeron/stm32f103
