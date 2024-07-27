ifeq ($(strip $(LEDS_ENABLE)), yes)
    OPT_DEFS += -DLEDS_ENABLE
    SRC += leds.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += thumbstick.c
    ANALOG_DRIVER_REQUIRED = yes
endif
