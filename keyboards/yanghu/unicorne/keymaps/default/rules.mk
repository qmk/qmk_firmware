ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
  SRC += oled.c
endif
