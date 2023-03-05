VIA_ENABLE = yes
ifeq ($(strip $(LEDS_ENABLE)), yes)
  OPT_DEFS += -DLEDS_ENABLE
  SRC += ../common/leds.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += ../common/oled.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
#  POINTING_DEVICE_ENABLE = yes
  OPT_DEFS += -DTHUMBSTICK_ENABLE
	SRC += analog.c
	SRC += ../common/thumbstick.c
endif
