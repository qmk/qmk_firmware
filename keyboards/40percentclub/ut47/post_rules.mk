ifeq ($(strip $(LED_ENABLE)), yes)
  OPT_DEFS += -DLED_ENABLE
  SRC += led.c
endif
