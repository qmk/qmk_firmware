ifeq ($(strip $(TRACKPOINT)), yes)
  POINTING_DEVICE_ENABLE = yes
  POINTING_DEVICE_DRIVER = ps2_mouse
  PS2_ENABLE = yes
  PS2_DRIVER = usart
  OPT_DEFS += -DUSART
endif

ifeq ($(strip $(AUTO_BUTTONS)), yes)
  OPT_DEFS += -DAUTO_BUTTONS
endif


