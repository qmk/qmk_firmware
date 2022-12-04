ifeq ($(strip $(TRACKPOINT)), yes)
  PS2_MOUSE_ENABLE = yes
  PS2_USE_USART = yes
  OPT_DEFS += -DUSART
endif

ifeq ($(strip $(AUTO_BUTTONS)), yes)
  OPT_DEFS += -DAUTO_BUTTONS
endif


