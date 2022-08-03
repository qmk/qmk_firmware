ifeq ($(strip $(TRACKPOINT)), yes)
  PS2_MOUSE_ENABLE = yes
  PS2_ENABLE = yes
PS2_DRIVER = usart
  OPT_DEFS += -DUSART
endif

ifeq ($(strip $(AUTO_BUTTONS)), yes)
  OPT_DEFS += -DAUTO_BUTTONS
endif


