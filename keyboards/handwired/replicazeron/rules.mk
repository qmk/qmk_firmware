AUDIO_ENABLE = no
BACKLIGHT_ENABLE = no
COMMAND_ENABLE = no
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog
LTO_ENABLE = yes # FIXME: If im not mistaken, this can cause issues on ARM (ie STM32)
OLED_ENABLE = yes
TAP_DANCE_ENABLE = no

LEDS_ENABLE = yes
THUMBSTICK_ENABLE = yes

SRC += common/state.c

# redirect compilation against "handwired/replicazeron" to the stm32 variant
DEFAULT_FOLDER = handwired/replicazeron/stm32f103

ifeq ($(strip $(LEDS_ENABLE)), yes)
    OPT_DEFS += -DLEDS_ENABLE
    SRC += common/leds.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += common/oled.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += analog.c \
           common/thumbstick.c
endif
