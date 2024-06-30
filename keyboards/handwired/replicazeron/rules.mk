JOYSTICK_ENABLE = yes
OLED_ENABLE = yes

LEDS_ENABLE = yes
THUMBSTICK_ENABLE = yes

LTO_ENABLE = yes

SRC += state.c

VPATH += keyboards/handwired/replicazeron/common

# redirect compilation against "handwired/replicazeron" to the stm32 variant
DEFAULT_FOLDER = handwired/replicazeron/stm32f103
