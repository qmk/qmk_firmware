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

ifeq ($(strip $(LEDS_ENABLE)), yes)
    OPT_DEFS += -DLEDS_ENABLE
    SRC += leds.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += analog.c \
           thumbstick.c
endif
